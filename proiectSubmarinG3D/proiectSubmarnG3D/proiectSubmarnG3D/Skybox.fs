#version 330 core

in vec2 TexCoords;  // Texture coordinates from vertex shader
in vec3 FragPos;    // Fragment position from vertex shader

out vec4 FragColor;  // Output color of the fragment

uniform samplerCube skybox;  // Cube map texture (skybox)
uniform vec3 lightColor;     // Light color for the scene

void main()
{
    // Sample the cube map texture using the texture coordinates
    vec4 texColor = texture(skybox, FragPos);  // Skybox texture color

    // Apply the light color to the sampled texture color
    FragColor = vec4(texColor.rgb * lightColor, texColor.a);  // Modulate with light color
}
