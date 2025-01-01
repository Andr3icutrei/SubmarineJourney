#pragma once
#pragma once
#include <string>
#include <glm.hpp>
#include "Model.h"
#include "Shader.h"
#include "IObject.h"

class Fish : public IObject
{
private:
	Model m_model;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_direction;
	glm::mat4 m_mat;

	float m_speed;
	float m_limitX, m_limitZ;
	float m_angle;
	bool m_reverse;
	glm::vec3 m_rotatedDirection;
public:
	Fish(const std::string& modelPath, glm::vec3 startPosition, glm::vec3 scale, float speed, float limitX, float limitZ,float angle);
	void update(float deltaTime);
	void draw(std::unique_ptr<Shader> &Shader);
	glm::vec3 getPosition();
	void setPosition(const glm::vec3& position);

	void setModelMatrix(glm::mat4 modelMatrix) { m_mat = modelMatrix; }
	glm::mat4& getModelMatrix() { return m_mat; }
};
