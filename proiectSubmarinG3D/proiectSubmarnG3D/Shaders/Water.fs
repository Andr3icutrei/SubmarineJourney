#version 330 core
out vec4 FragColor;

in vec2 TexCoord;   // Texture coordinates from vertex shader
in vec3 FragPos;    // Fragment position in world space
in vec3 Normal;     // Interpolated normal vector from vertex shader

uniform vec3 lightDir;      // Normalized light direction (from application)
uniform vec3 viewPos;       // Position of the camera (viewer) in world space
uniform vec3 lightColor;    // Light color for illumination

uniform sampler2D waterTexture; // Texture for water surface
uniform sampler2D sandTexture;  // Texture for bottom (sand)
uniform int isBottomFace;       // Flag to indicate if it's the bottom face

uniform float time;             // Time for animating waves

void main()
{
    vec3 baseColor;
    vec2 uv;
    vec3 finalColor;

    // Normalize the interpolated normal
    vec3 norm = normalize(Normal);

    if (isBottomFace == 1) {
        // Sand face (no waves)
        uv = TexCoord;  // Use standard texture coordinates for the bottom
        baseColor = texture(sandTexture, uv).rgb;  
        finalColor = baseColor;
    } else {
        // Water face (apply waves)
        vec2 texCoord = FragPos.xz * 0.1; // Scale texture coordinates

        // Modulate wave amplitude based on light direction
        float waveAmplitude = 0.02 + 0.01 * max(dot(norm, lightDir), 0.0);

        // Create dynamic waves influenced by light
        vec2 uvOffset = vec2(0.0, sin(time * 1.5 + FragPos.x * 0.5) * waveAmplitude); 
        uv = texCoord + uvOffset;

        baseColor = texture(waterTexture, uv).rgb;

        // Mix base color with a blue tint for water
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
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, alpha) * vec4(finalColor, 1.0);
}
