#pragma once

#include <string>
#include <glm.hpp>
#include "IObject.h"
#include "Model.h"
#include "Shader.h"

class Coral: public IObject
{
private:
	Model m_model;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::mat4 m_mat;
public:
	Coral(const std::string& modelPath, glm::vec3 position, glm::vec3 scale);
	void draw(Shader& shader);

	void setPosition(const glm::vec3& position);
	glm::vec3 getPosition();
	void setScale(const glm::vec3& scale);
	glm::vec3 getScale();

	void setModelMatrix(glm::mat4 modelMatrix) { m_mat = modelMatrix; }
	glm::mat4& getModelMatrix() { return m_mat; }
};