#version 330 core

layout(location = 0) in vec3 aPos;  // Vertex position
layout(location = 1) in vec2 aTexCoord;  // Texture coordinate

out vec2 TexCoords;  // Pass texture coordinates to fragment shader
out vec3 FragPos;    // Pass fragment position to fragment shader

uniform mat4 projection;  // Projection matrix
uniform mat4 view;        // View matrix

void main()
{
    // Set the fragment position and texture coordinates
    FragPos = aPos;  // No need for transformation since the skybox is at infinity
    TexCoords = aTexCoord;

    // Apply projection and view transformations to the position
    gl_Position = projection * view * vec4(aPos, 1.0f);
}
