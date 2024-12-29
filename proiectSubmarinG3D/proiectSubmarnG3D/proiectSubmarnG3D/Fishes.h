#pragma once
#pragma once
#include <string>
#include <glm.hpp>
#include "Model.h"
#include "Shader.h"

class Fish
{
private:
	Model m_model;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_direction;

	float m_speed;
	float m_limitX, m_limitZ;
	float m_angle;

public:
	Fish(const std::string& modelPath, glm::vec3 startPosition, glm::vec3 scale, float speed, float limitX, float limitZ);
	void update(float deltaTime);
	void draw(std::unique_ptr<Shader> &Shader);
	glm::vec3 getPosition();
	void setPosition(const glm::vec3& position);

};
