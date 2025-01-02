#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aPos;      // Vertex position
layout(location = 1) in vec3 aNormal;   // Vertex normal
layout(location = 2) in vec2 aTexCoord; // Texture coordinates

// Output to fragment shader
out vec2 texCoord;
out vec3 fragPos;  // Fragment position in world space
out vec3 normal;   // Normal in world space
out vec4 fragPosLightSpace;  // Fragment position in light space

// Uniforms for transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;  // Matrix to transform positions to light space

void main()
{
    // Calculate fragment position in world space
    fragPos = vec3(model * vec4(aPos, 1.0));

    // Calculate fragment position in light space
    fragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);

    // Pass normal in world space (account for model transformation)
    normal = mat3(transpose(inverse(model))) * aNormal;

    // Pass texture coordinates
    texCoord = aTexCoord;

    // Apply transformation for position and projection
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}