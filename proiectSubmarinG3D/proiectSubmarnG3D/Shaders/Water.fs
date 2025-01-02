#version 330 core
out vec4 FragColor;

in vec2 TexCoord;   // Texture coordinates from vertex shader
in vec3 FragPos;    // Fragment position in world space
in vec3 Normal;     // Interpolated normal vector from vertex shader
in vec4 FragPosLightSpace;  // Fragment position in light space (for shadow)

uniform vec3 lightDir;      // Normalized light direction (from application)
uniform vec3 viewPos;       // Position of the camera (viewer) in world space
uniform vec3 lightColor;    // Light color for illumination

uniform sampler2D waterTexture; // Texture for water surface
uniform sampler2D sandTexture;  // Texture for bottom (sand)
uniform int isBottomFace;       // Flag to indicate if it's the bottom face

uniform float time;             // Time for animating waves

// Shadow map
uniform sampler2D shadowMap;  // The shadow map
uniform float nearPlane;      // Near plane for shadow depth mapping
uniform float farPlane;       // Far plane for shadow depth mapping

float ShadowCalculation(vec4 fragPosLightSpace) {
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; // Normalizare
    projCoords = projCoords * 0.5 + 0.5; // Din [-1, 1] în [0, 1]

    if (projCoords.z > 1.0)
        return 0.0;

    float closestDepth = texture(shadowMap, projCoords.xy).r; // Adâncime din hart?
    float currentDepth = projCoords.z;

    float bias = 0.005; // Compensare pentru artefacte
    return currentDepth > closestDepth + bias ? 1.0 : 0.0;
}

void main()
{
    vec3 baseColor;
    vec3 finalColor;
    float shadow=0.0;
    // Normalize the interpolated normal
    vec3 norm = normalize(Normal);

    if (isBottomFace == 1) {
        // Sand face (no waves, apply shadow)
        vec2 uv = TexCoord;  // Use standard texture coordinates for the bottom
        baseColor = texture(sandTexture, uv).rgb;

        // Calculate shadow on sand face
        shadow = ShadowCalculation(FragPosLightSpace);
        finalColor = baseColor;

    } else {
        // Water face (apply waves, no shadow)
        vec2 texCoord = FragPos.xz * 0.1; // Scale texture coordinates

        // Modulate wave amplitude based on light direction
        float waveAmplitude = 0.02 + 0.01 * max(dot(norm, lightDir), 0.0);

        // Create dynamic waves influenced by light
        vec2 uvOffset = vec2(0.0, sin(time * 1.5 + FragPos.x * 0.5) * waveAmplitude); 
        vec2 uv = texCoord + uvOffset;

        baseColor = texture(waterTexture, uv).rgb;

        finalColor = baseColor;
    }

    // Ambient lighting
    float ambientStrength = 0.8;  // Increased ambient strength for brighter water
    vec3 ambient = ambientStrength * finalColor * lightColor;

    // Diffuse lighting (Lambertian reflectance)
    float diff = max(dot(norm, lightDir), 0.0);
    float diffuseStrength = 1.0;  // Increased diffuse strength for more brightness
    vec3 diffuse = diffuseStrength * diff * finalColor * lightColor;

    // Specular lighting (Phong reflection model)
    vec3 viewDir = normalize(viewPos - FragPos);  // Direction from fragment to the camera
    vec3 reflectDir = reflect(-lightDir, norm);  // Reflection vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // Specular highlight
    float specularStrength = 1.0;  // Increased specular strength for brighter highlights
    vec3 specular = specularStrength * spec * vec3(1.0) * lightColor;

    // Set alpha for water transparency (semi-transparent water)
    float alpha = 0.5;

    // Final fragment color with lighting and base texture
    vec3 result = ambient + (1.0-shadow)*(diffuse + specular);
    FragColor = vec4(result, alpha) * vec4(finalColor, 1.0);
}
