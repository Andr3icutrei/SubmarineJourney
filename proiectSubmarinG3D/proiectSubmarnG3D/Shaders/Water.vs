#version 330 core
layout (location = 0) in vec3 aPos;       // Vertex position
layout (location = 1) in vec2 aTexCoord; // Vertex texture coordinate
layout (location = 2) in vec3 aNormal;   // Vertex normal

out vec2 TexCoord;  // Pass texture coordinate to fragment shader
out vec3 FragPos;   // Pass fragment position in world space
out vec3 Normal;    // Pass normal vector to fragment shader

uniform mat4 model;       // Model matrix
uniform mat4 view;        // View matrix
uniform mat4 projection;  // Projection matrix

void main()
{
    // Pass texture coordinates directly
    TexCoord = aTexCoord;

    // Compute fragment position in world space
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Correctly transform the normal vector
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Compute final vertex position in clip space
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
