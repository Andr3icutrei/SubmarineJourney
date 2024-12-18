#version 330 core

out vec4 FragColor;

in vec2 TexCoord;    // Texture coordinates (for submarine texture)
in vec3 FragPos;     // World space position of the fragment
in vec3 Normal;      // World space normal of the fragment

uniform vec3 lightDir;    // Directional light direction (e.g., sun direction)
uniform vec3 lightColor;  // Color of the light
uniform vec3 viewPos;     // Camera position (view position)
uniform sampler2D texture_diffuse1; // Diffuse texture for the submarine

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

    // Final color: Apply lighting and texture color
    FragColor = vec4(result, 1.0) * texColor;
}
