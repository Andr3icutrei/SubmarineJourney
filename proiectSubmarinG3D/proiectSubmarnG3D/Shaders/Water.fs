#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos; 
uniform vec3 viewPos;  
uniform vec3 lightColor;

uniform sampler2D waterTexture; 
uniform sampler2D sandTexture;  
uniform int isBottomFace;        

void main()
{
    float ambientStrength = 0.6;
    float diffuseStrength = 0.7;
    float specularStrength = 0.8;

    vec4 baseColor;
    if (isBottomFace == 1) {
        baseColor = texture(sandTexture, TexCoord);  
    } else {
        baseColor = texture(waterTexture, TexCoord);
    }

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 ambient = ambientStrength * vec3(baseColor);                  
    vec3 diffuse = diffuseStrength * diff * vec3(baseColor);           
    vec3 specular = specularStrength * spec * vec3(1.0);            

    vec3 result = ambient + diffuse + specular;

    float alpha = baseColor.a * 0.5;  

    FragColor = vec4(result, alpha);
}
