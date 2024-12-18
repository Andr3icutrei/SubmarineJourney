#version 330 core
out vec4 FragColor;

in vec2 TexCoord;   // Texture coordinates from vertex shader
in vec3 FragPos;    // Fragment position in world space
in vec3 Normal;     // Interpolated normal vector from vertex shader

uniform vec3 lightPos;     // Position of the light source in world space
uniform vec3 viewPos;      // Position of the camera (viewer) in world space
uniform vec3 lightColor;   // Light color for illumination

uniform sampler2D waterTexture; // Texture for water surface
uniform sampler2D sandTexture;  // Texture for bottom (sand)
uniform int isBottomFace;       // Flag to indicate if it's the bottom face

void main()
{
    // Base color: Water texture or Sand texture based on the face
    vec4 baseColor;
    if (isBottomFace == 1) {
        baseColor = texture(sandTexture, TexCoord);  
    } else {
        baseColor = texture(waterTexture, TexCoord);
    }

    // Normalize the interpolated normal and calculate light direction
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); // Direction from fragment to light source

    // Ambient lighting
    float ambientStrength = 0.8;  // Increased ambient strength for brighter water
    vec3 ambient = ambientStrength * vec3(baseColor) * lightColor;

    // Diffuse lighting (Lambertian reflectance)
    float diff = max(dot(norm, lightDir), 0.0);
    float diffuseStrength = 1.0;  // Increased diffuse strength for more brightness
    vec3 diffuse = diffuseStrength * diff * vec3(baseColor) * lightColor;

    // Specular lighting (Phong reflection model)
    vec3 viewDir = normalize(viewPos - FragPos);  // Direction from fragment to the camera
    vec3 reflectDir = reflect(-lightDir, norm);  // Reflection vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // Specular highlight
    float specularStrength = 1.0;  // Increased specular strength for brighter highlights
    vec3 specular = specularStrength * spec * vec3(1.0) * lightColor;

    // Combine ambient, diffuse, and specular components
    vec3 result = ambient + diffuse + specular;

    // Increase brightness by multiplying by a factor (e.g., 1.2)
    result *= 1.2;

    // Set alpha for water transparency (semi-transparent water)
    float alpha = baseColor.a * 0.5;

    // Final fragment color with lighting and base texture
    FragColor = vec4(result, alpha) * baseColor;
}

