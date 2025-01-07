#pragma once
#include <GLM.hpp>

#include <string>

#include "Model.h"
#include "Shader.h"

class Chest
{
private:
    Model m_model;

    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::mat4 m_modelMatrix;
public:
    Chest(std::string filePath);

    void setPosition(const glm::vec3& position) { m_position = position; }
    glm::vec3& getPosition() { return m_position; }

    void setScale(const glm::vec3& scale) { m_scale = scale; }
    glm::vec3& getScale() { return m_scale; }
  
    glm::mat4& getModelMatrix() { return m_modelMatrix; }
    void setModelMatrix(const glm::mat4& model) { m_modelMatrix = model; }
   
    void draw(Shader& shader);
    void appear(glm::vec3 position, glm::vec3 scale);

};

