#pragma once
#include <glm.hpp>
#include "stb_image.h"
#include "Model.h"

class Skybox
{
private:
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;
    glm::vec3 position;
    glm::vec3 scale;
    void setupSkybox();
    void loadTexture(const char* skyPath);
public:
    Skybox(const char* skyPath);
    ~Skybox();
    void draw(Shader& shader);
    unsigned int getTextureID() const { return textureID; }
};

