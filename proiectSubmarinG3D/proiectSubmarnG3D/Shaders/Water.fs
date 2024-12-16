#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;  // Light position
uniform vec3 viewPos;   // Camera position
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform sampler2D waterTexture;  // Water texture
uniform sampler2D sandTexture;   // Sand texture
uniform int isBottomFace;        // 1 if bottom face, 0 otherwise

void main()
{
    float ambientStrength = 0.8;
    float diffuseStrength = 0.9;
    float specularStrength = 0.7;

    // Choose the appropriate texture based on isBottomFace
    vec4 baseColor;
    if (isBottomFace == 1) {
        baseColor = texture(sandTexture, TexCoord);  // Use sand texture
    } else {
        baseColor = texture(waterTexture, TexCoord); // Use water texture
    }

    // Lighting calculations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // Specular highlight
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    // Combine the results
    vec3 ambient = ambientStrength * vec3(baseColor);                   // Ambient lighting
    vec3 diffuse = diffuseStrength * diff * vec3(baseColor);           // Diffuse lighting
    vec3 specular = specularStrength * spec * lightColor * vec3(1.0);               // Specular lighting

    vec3 result = ambient + diffuse + specular;

    // Adjust the alpha value to make the texture partially transparent
    float alpha = baseColor.a * 0.5;  // 50% transparency with texture alpha

    FragColor = vec4(result, alpha);
}
