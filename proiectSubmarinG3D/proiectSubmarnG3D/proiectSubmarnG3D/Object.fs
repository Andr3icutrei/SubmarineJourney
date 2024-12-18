#version 330 core

in vec3 fragPos;       // Fragment position in world space
in vec3 normal;        // Normal vector at the fragment's location
in vec2 texCoord;      // Texture coordinates passed from the vertex shader

out vec4 FragColor;    // Output color of the fragment

// Light properties (you would usually pass these as uniforms)
uniform vec3 lightPos;     // Position of the light source (e.g., sun)
uniform vec3 lightColor;   // Color of the light source (e.g., white light)
uniform vec3 viewPos;      // Camera position (used for specular calculation)
uniform sampler2D texture1; // The texture of the object

void main()
{
    // Texture sampling
    vec3 objectColor = texture(texture1, texCoord).rgb; // Sample the texture

    // Ambient lighting (constant light)
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting (based on the angle between the surface normal and light direction)
    vec3 norm = normalize(normal);                  // Normalize the normal vector
    vec3 lightDir = normalize(lightPos - fragPos);  // Direction from fragment to light source
    float diff = max(dot(norm, lightDir), 0.0);     // Dot product gives cosine of angle
    vec3 diffuse = diff * lightColor;               // Scale diffuse light by light color

    // Specular lighting (shiny highlights)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);                // Direction from fragment to camera
    vec3 reflectDir = reflect(-lightDir, norm);                 // Reflection of the light vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // Phong specular reflection
    vec3 specular = specularStrength * spec * lightColor;       // Specular component

    // Final color computation: combine ambient, diffuse, and specular with the texture
    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0); // Final fragment color
}
