#version 330 core

layout(location = 0) in vec3 aPos;       // Object vertex position
layout(location = 1) in vec3 aNormal;    // Object normal
layout(location = 2) in vec2 aTexCoord;  // Object texture coordinates

out vec3 fragPos;        // Position of the fragment (for lighting calculations)
out vec3 normal;         // Normal vector (for lighting calculations)
out vec2 texCoord;       // Texture coordinates

uniform mat4 model;      // Model matrix (transformation of the object)
uniform mat4 view;       // View matrix (camera transformation)
uniform mat4 projection; // Projection matrix (perspective projection)

void main()
{
    fragPos = vec3(model * vec4(aPos, 1.0));  // Transform vertex position to world space
    normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal to world space
    texCoord = aTexCoord; // Pass texture coordinates to fragment shader

    gl_Position = projection * view * vec4(fragPos, 1.0); // Final position in clip space
}
