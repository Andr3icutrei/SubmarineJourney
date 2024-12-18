#version 330 core

layout(location = 0) in vec3 aPos;  // Vertex position
layout(location = 1) in vec3 aNormal;  // Vertex normal

out vec3 TexCoords;  // Pass texture coordinates to fragment shader
out vec3 FragNormal; // Pass normal to fragment shader

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;  // Model matrix (including scaling)

void main()
{
    TexCoords = aPos;  // Skybox coordinates are the vertex positions
    FragNormal = mat3(transpose(inverse(model))) * aNormal;  // Transform the normal to world space
    gl_Position = projection * view * model * vec4(aPos, 1.0f);  // Apply view, projection, and model (scaling) transformations
}

