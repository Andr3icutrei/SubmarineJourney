#version 330 core

in vec3 fragPos;       // Fragment position in world space
in vec3 normal;        // Normal vector at the fragment's location
in vec2 texCoord;      // Texture coordinates passed from the vertex shader
in vec4 fragPosLightSpace;  // Fragment position in light space (passed from vertex shader)

out vec4 FragColor;    // Output color of the fragment

// Light properties (you would usually pass these as uniforms)
uniform vec3 lightPos;     // Position of the light source (e.g., sun)
uniform vec3 lightColor;   // Color of the light source (e.g., white light)
uniform vec3 viewPos;      // Camera position (used for specular calculation)
uniform sampler2D texture_diffuse1; // The texture of the object

// Shadow map and parameters
uniform sampler2D shadowMap;  // The shadow map

// Function to calculate shadow intensity based on the depth from the shadow map
float ShadowCalculation(vec4 fragPosLightSpace) 
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    if (projCoords.z > 1.0)
        return 0.0;

    float shadow = 0.0;
    float bias = 0.005; // Bias adjusted
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0); // Texel size

    // 3x3 PCF filtering
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float closestDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += (projCoords.z > closestDepth + bias) ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0; // Average shadow value

    return shadow;
}

void main()
{
    // Texture sampling
    vec3 objectColor = texture(texture_diffuse1, texCoord).rgb; // Sample the texture

    // Ambient lighting (constant light)
    float ambientStrength = 0.7; // Increased ambient strength
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting (based on the angle between the surface normal and light direction)
    vec3 norm = normalize(normal);                  // Normalize the normal vector
    vec3 lightDir = normalize(lightPos - fragPos);  // Direction from fragment to light source
    float diff = max(dot(norm, lightDir), 0.0);     // Dot product gives cosine of angle
    vec3 diffuse = diff * lightColor;               // Scale diffuse light by light color

    // Specular lighting (shiny highlights)
    float specularStrength = 0.7; // Reduced specular strength
    vec3 viewDir = normalize(viewPos - fragPos);                // Direction from fragment to camera
    vec3 reflectDir = reflect(-lightDir, norm);                 // Reflection of the light vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // Phong specular reflection
    vec3 specular = specularStrength * spec * lightColor;       // Specular component

    // Shadow Calculation
    float shadow = ShadowCalculation(fragPosLightSpace);

    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0); // Final fragment color with shadow effect
}
