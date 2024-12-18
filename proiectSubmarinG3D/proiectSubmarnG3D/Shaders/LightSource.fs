#version 330 core

out vec4 FragColor;

in vec2 TexCoord;  // Texture coordinates from vertex shader
in vec3 FragPos;   // World space position from vertex shader
in vec3 Normal;    // Normal from vertex shader

uniform vec3 lightDir;    // Direction of the directional light
uniform vec3 lightColor;  // Color of the light
uniform sampler2D texture_diffuse1;  // Texture for the light source

void main()
{
    // Normalize normal and light direction
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightDir);
    
    // Ambient lighting (constant low light)
    float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting (Lambert's cosine law)
    float diff = max(dot(norm, -lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Combine the results: ambient + diffuse
    vec3 result = (ambient + diffuse);
    
    // Get the texture color
    vec4 texColor = texture(texture_diffuse1, TexCoord);
    
    // Final color: Apply lighting and texture color
    FragColor = vec4(result, 1.0) * texColor;
}
