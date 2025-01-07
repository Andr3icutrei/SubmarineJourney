#version 330 core

in vec3 TexCoords;in vec3 FragNormal; // Normal from vertex shader

out vec4 FragColor;  // Output color of the fragment

uniform samplerCube skybox;  // Skybox texture
uniform vec3 lightColor;     // Color of the directional light
uniform vec3 lightDir;       // Direction of the directional light
uniform vec3 viewPos;        // Position of the camera/viewer

void main()
{
    // Sample the skybox color
    vec3 skyboxColor = texture(skybox, TexCoords).rgb;
    
    // Normalize the normal and light direction
    vec3 norm = normalize(FragNormal);
    vec3 lightDirNorm = normalize(lightDir);
    
    // Ambient lighting
    vec3 ambient = 0.8 * lightColor;  // Ambient lighting (low intensity)

    // Diffuse lighting
    float diff = max(dot(norm, lightDirNorm), 0.0);
    vec3 diffuse = diff * lightColor; // Diffuse lighting (based on angle with normal)
    
    // Specular lighting
    vec3 viewDir = normalize(viewPos - TexCoords);  // Direction to the camera/viewer
    vec3 reflectDir = reflect(-lightDirNorm, norm);  // Reflection of the light direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // Specular factor
    vec3 specular = spec * lightColor;  // Specular lighting (highlight based on angle with camera)

    // Combine all the lighting components
    vec3 finalColor = (ambient + diffuse + specular) * skyboxColor;
    
    // Output the final color
    FragColor = vec4(finalColor, 1.0);
}
