#version 330 core

in vec3 FragPos;    // Fragment position
in vec3 Normal;     // Fragment normal
in vec3 LightPos;   // Light position
in vec3 ViewPos;    // View position

out vec4 FragColor;

uniform vec3 lightColor;    // Light color (e.g., white light)
uniform vec3 objectColor;   // Object color (e.g., diffuse color)
uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;

void main()
{
    // Normalizing vectors
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);  // Direction from fragment to light
    vec3 viewDir = normalize(ViewPos - FragPos);    // Direction from fragment to camera

    // Ambient component

    vec3 ambient = ambientStrength * lightColor;

    // Diffuse component
    float diff = max(dot(norm, lightDir), 0.0);  // Lambertian reflection
    vec3 diffuse = diff * lightColor;

    // Specular component (Phong reflection model)

    vec3 reflectDir = reflect(-lightDir, norm);   // Reflect light direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // Phong specular
    vec3 specular = specularStrength * spec * lightColor;

    // Combine results
    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0); // Output the final color
}
