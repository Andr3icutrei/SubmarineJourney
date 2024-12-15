#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform sampler2D waterTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 waterColor;

void main()
{
    vec4 texColor = texture(waterTexture, TexCoords);

    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuse = max(dot(Normal, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);

    vec3 resultColor = (diffuse * lightColor * texColor.rgb) + (spec * lightColor);
    resultColor = mix(waterColor, resultColor, 0.5);

    FragColor = vec4(resultColor, 1.0);
}
