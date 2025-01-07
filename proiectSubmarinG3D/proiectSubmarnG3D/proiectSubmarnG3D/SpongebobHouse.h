#pragma once
#include <GLM.hpp>

#include <string>

#include "Model.h"
#include "Shader.h"

class SpongebobHouse
{
public:
    SpongebobHouse(std::string filename);

    glm::mat4& getModelMatrix() { return m_modelMatrix; }
    glm::vec3& getPosition() { return m_position; }
    glm::vec3& getScale() { return m_scale; }

    void setModelMatrix(const glm::mat4& model) { m_modelMatrix = model; }
    void setPosition(const glm::vec3& position) { m_position = position; }
    void setScale(const glm::vec3& scale) { m_scale = scale; }

    void draw(Shader& shader);
    void appear(glm::vec3 position, glm::vec3 scale);
private:
    glm::mat4 m_modelMatrix;
    glm::vec3 m_position;
    glm::vec3 m_scale;

    Model m_model;
};

