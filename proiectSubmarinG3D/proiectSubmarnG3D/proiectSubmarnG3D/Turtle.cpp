#include "Turtle.h"
Turtle::Turtle(const std::string& modelPath, glm::vec3 position, glm::vec3 scale) :
	m_model(modelPath, false),
	m_position(position),
	m_scale(scale),
	m_radius(0.f),
	m_velocity(0.0f, 0.f, 0.f),
	m_speed(1.f)
{
	//m_radius = glm::length(glm::vec2(m_position.x, m_position.z));
	m_mat = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale);
}
void Turtle::draw(std::unique_ptr<Shader>& shader)
{
	shader->use();
	shader->setMat4("model", m_mat);
	m_model.Draw(*shader);
}

void Turtle::update(float deltaTime)
{
	m_position += m_velocity * m_speed * deltaTime;
	if (m_radius > 0.0f)
	{
		float distanceFromCenter = glm::length(glm::vec2(m_position.x, m_position.z));

		if (distanceFromCenter > m_radius)
		{
			glm::vec3 directionToCenter = glm::normalize(glm::vec3(m_position.x, 0.0f, m_position.z));
			m_position = directionToCenter * m_radius;
		}
	}
	m_mat = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale);
}

glm::vec3 Turtle::getPosition()
{
	return m_position;
}

void Turtle::setPosition(const glm::vec3& position)
{
	m_position = position;
	m_mat = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale);
}

void Turtle::setScale(const glm::vec3& scale)
{
	m_scale = scale;
	m_mat = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale);
}

glm::vec3 Turtle::getScale()
{
	return m_scale;
}

void Turtle::setSpeed(float speed)
{
	m_speed = speed;
}

float Turtle::getSpeed()
{
	return m_speed;
}

void Turtle::setRadius(float radius)
{
	m_radius = radius;
}

glm::vec3 Turtle::getVelocity()
{
	return m_velocity;
}


void Turtle::setVelocity(const glm::vec3& velocity)
{
	m_velocity = velocity;
}
