#version 330 core

in vec3 TexCoords;  // Texture coordinates from vertex shader

out vec4 FragColor;  // Output color of the fragment

uniform samplerCube skybox;  //here

void main()
{
    FragColor = texture(skybox, TexCoords);  // Sample the skybox texture
}
