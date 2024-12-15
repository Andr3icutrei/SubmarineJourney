#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;  // Light position
uniform vec3 viewPos;   // Camera position

uniform sampler2D texture1;  // Cube texture

void main()
{
    // Lighting calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // Specular highlight
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // Combine the results
    vec3 ambient = 0.1 * vec3(texture(texture1, TexCoord));  // Ambient lighting
    vec3 diffuse = diff * vec3(texture(texture1, TexCoord));  // Diffuse lighting
    vec3 specular = spec * vec3(1.0);  // Specular lighting

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
