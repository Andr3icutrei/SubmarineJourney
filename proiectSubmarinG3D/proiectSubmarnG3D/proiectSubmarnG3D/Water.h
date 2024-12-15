#pragma once
#include "Model.h"
#include "glm.hpp"
#include "Shader.h"
#include "IObject.h"
#include "stb_image.h"
#include <string>

class Water {
private:
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;
    glm::vec3 position;
    glm::vec3 scale;

    void setupWater();
    void loadTexture(const char* texturePath);

public:
    Water(const glm::vec3& position, const glm::vec3& scale, const char* texturePath);
    ~Water();

    void draw(Shader& shader);
};

