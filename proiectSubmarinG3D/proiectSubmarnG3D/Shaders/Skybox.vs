#version 330 core

layout(location = 0) in vec3 aPos;  // Vertex position

out vec3 TexCoords;  // Pass texture coordinates to fragment shader

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;  // New model matrix (including scaling)

void main()
{
    TexCoords = aPos;  // Skybox coordinates are the vertex positions
    gl_Position = projection * view * model * vec4(aPos, 1.0f);  // Apply view, projection, and model (scaling) transformations
}
