#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aPos;      // Vertex position
layout(location = 1) in vec3 aNormal;   // Vertex normal
layout(location = 2) in vec2 aTexCoord; // Texture coordinates

// Output to fragment shader
out vec2 TexCoord;
out vec3 FragPos;  // Fragment position in world space
out vec3 Normal;   // Normal in world space

// Uniforms for transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Calculate fragment position in world space
    FragPos = vec3(model * vec4(aPos, 1.0));

    // Pass normal in world space (account for model transformation)
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Pass texture coordinates
    TexCoord = aTexCoord;

    // Apply transformation for position and projection
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
