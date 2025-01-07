#pragma once

#include <string>
#include "IObject.h"
#include "Model.h"
#include "Shader.h"

class Turtle : public IObject
{
private:
	Model m_model;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_velocity;
	glm::mat4 m_mat;

	float m_speed;
	float m_radius;

public:
	Turtle(const std::string& modelPath, glm::vec3 position, glm::vec3 scale);

	void draw(std::unique_ptr<Shader>& shader);
	void update(float deltaTime);

	glm::vec3 getPosition();
	void setPosition(const glm::vec3& position);
	void setScale(const glm::vec3& scale);
	glm::vec3 getScale();
	void setSpeed(float speed);
	float getSpeed();
	void setRadius(float radius);
	glm::vec3 getVelocity();
	void setVelocity(const glm::vec3& velocity);

	void setModelMatrix(glm::mat4 modelMatrix) { m_mat = modelMatrix; }
	glm::mat4& getModelMatrix() { return m_mat; }
};
