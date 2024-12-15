#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;  // Normal attribute

out vec2 TexCoord;
out vec3 FragPos;  // Pass the position to the fragment shader
out vec3 Normal;   // Pass the normal to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoord = aTexCoord;
    FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate fragment position in world space
    Normal = mat3(transpose(inverse(model))) * aNormal;  // Correct normal transformation
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
