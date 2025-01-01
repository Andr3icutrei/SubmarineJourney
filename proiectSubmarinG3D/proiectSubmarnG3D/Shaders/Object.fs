#version 330 core

out vec4 FragColor;

in vec2 TexCoord;      // Texture coordinates (for submarine texture)
in vec3 FragPos;       // World space position of the fragment
in vec3 Normal;        // World space normal of the fragment
in vec4 FragPosLightSpace;  // Fragment position in light space

uniform vec3 lightDir;    // Directional light direction (e.g., sun direction)
uniform vec3 lightColor;  // Color of the light
uniform vec3 viewPos;     // Camera position (view position)
uniform sampler2D texture_diffuse1; // Diffuse texture for the submarine
uniform sampler2D shadowMap;   // Shadow map sampler

// Function to calculate the shadow factor
float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Perform perspective divide to get the normalized device coordinates
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    
    // Transform from [0,1] to [0,1] range (NDC space)
    projCoords = projCoords * 0.5 + 0.5;

    // Check if the fragment is within the bounds of the shadow map
    if (projCoords.z > 1.0 || projCoords.x < 0.0 || projCoords.x > 1.0 || projCoords.y < 0.0 || projCoords.y > 1.0)
        return 0.0;

    // Sample the depth from the shadow map at the given coordinates
    float closestDepth = texture(shadowMap, projCoords.xy).r;  // Depth value from shadow map
    float currentDepth = projCoords.z;  // Depth value of the current fragment

    // Shadow bias to avoid shadow acne
    float bias = 0.005;

    // Return 1.0 (no shadow) if the current fragment is in front of the shadow map
    // Return 0.0 (shadow) otherwise
    return currentDepth - bias > closestDepth ? 0.0 : 1.0;
}

void main()
{
    // Normalize the normal and light direction
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightDir);

    // Ambient lighting (constant low light)
    float ambientStrength = 0.6;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting (Lambert's cosine law)
    float diff = max(dot(norm, -lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting (Phong reflection model)
    float specularStrength = 0.6;
    vec3 viewDir = normalize(viewPos - FragPos); // View direction
    vec3 reflectDir = reflect(lightDirection, norm); // Reflected light direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // Shininess factor
    vec3 specular = specularStrength * spec * lightColor;

    // Combine the results: ambient + diffuse + specular
    vec3 result = (ambient + diffuse + specular);

    // Get the texture color
    vec4 texColor = texture(texture_diffuse1, TexCoord);

    // Apply shadow to the final color based on the shadow calculation
    float shadow = ShadowCalculation(FragPosLightSpace);

    // Final color: Apply lighting, shadow, and texture color
    FragColor = vec4(result, 1.0) * texColor * shadow;
}
