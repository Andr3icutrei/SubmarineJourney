#version 330 core

layout (location = 0) in vec3 aPos;     // Vertex position
layout (location = 1) in vec3 aNormal;  // Vertex normal

out vec3 FragPos;     // Fragment position
out vec3 Normal;      // Fragment normal
out vec3 LightPos;    // Light position
out vec3 ViewPos;     // View position

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos; // Light position in world space
uniform vec3 viewPos;  // Camera/view position

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate fragment position in world space
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal to world space
    LightPos = lightPos;
    ViewPos = viewPos;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
