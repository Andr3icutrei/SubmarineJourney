#include "Water.h"

void Water::setupWater()
{    float vertices[] = {
        // Positions         // Texture Coords  // Normals
        // Front face
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f, // Bottom-left
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f, // Bottom-right
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f, // Top-right
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // Top-left

        // Back face
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f, // Bottom-left
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f, // Bottom-right
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f, // Top-right
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f, // Top-left

        // Left face
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  -1.0f, 0.0f, 0.0f, // Bottom-back
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,  -1.0f, 0.0f, 0.0f, // Bottom-front
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  -1.0f, 0.0f, 0.0f, // Top-front
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  -1.0f, 0.0f, 0.0f, // Top-back

        // Right face
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f, // Bottom-back
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f, // Bottom-front
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f, // Top-front
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f, // Top-back

         // Top face
         -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f, // Back-left
          0.5f,  0.5f, -0.5f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f, // Back-right
          0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f, // Front-right
         -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f, // Front-left

         // Bottom face
         -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f, // Back-left
          0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f, // Back-right
          0.5f, -0.5f,  0.5f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f, // Front-right
         -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f  // Front-left
    };

    unsigned int indices[] = {
        // Front face
        0, 1, 2,
        0, 2, 3,
        // Back face
        4, 5, 6,
        4, 6, 7,
        // Left face
        8, 9, 10,
        8, 10, 11,
        // Right face
        12, 13, 14,
        12, 14, 15,
        // Top face
        16, 17, 18,
        16, 18, 19,
        // Bottom face
        20, 21, 22,
        20, 22, 23
    };

    // OpenGL buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

}

void Water::loadTexture(const char* waterTexturePath, const char* sandTexturePath)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(waterTexturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load water texture: " << waterTexturePath << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &sandTextureID);
    glBindTexture(GL_TEXTURE_2D, sandTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load(sandTexturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load sand texture: " << sandTexturePath << std::endl;
    }
    stbi_image_free(data);
}

Water::Water(const glm::vec3& position, const glm::vec3& scale, const char* waterTexturePath, const char* sandTexturePath)
    : position(position), scale(scale)
{
    setupWater();
    loadTexture(waterTexturePath,sandTexturePath);
}

Water::~Water() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &textureID);
    glDeleteTextures(1, &sandTextureID);
}

glm::vec3 Water::getPosition()
{
    return position;
}

glm::vec3 Water::getScale()
{
    return scale;
}

void Water::draw(Shader& shader)
{
    shader.use();


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position + glm::vec3(0.f, -6.f, 0.f));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);

    shader.setInt("waterTexture", 0);
    shader.setInt("sandTexture", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, sandTextureID);

    for (int i = 0; i < 6; ++i) {
        if (i == 5) {            shader.setInt("isBottomFace", 1);
        }
        else {
            shader.setInt("isBottomFace", 0);
        }
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(unsigned int)));
    }

    glBindVertexArray(0);
}

float Water::getSurface()
{
    return position.y;
}

float Water::getBottom()
{
    return position.y - scale.y;
}

float Water::getDistanceFromCenter()
{
    return scale.x / 2;
}


