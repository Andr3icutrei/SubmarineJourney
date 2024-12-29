#include "Fishes.h"

Fish::Fish(const std::string& modelPath, glm::vec3 startPosition, glm::vec3 scale, float speed, float limitX, float limitZ)
	:m_model(modelPath, false),
	m_position(startPosition),
	m_scale(scale),
	m_direction(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_speed(speed),
	m_limitX(limitX),
	m_limitZ(limitZ),
	m_angle(0.0f)
{}

void Fish::update(float deltaTime)
{
	//
	m_angle += m_speed * deltaTime;
	if (m_angle > 360.0f)
		m_angle -= 360.0f;
	m_position.x = m_limitX * cos(glm::radians(m_angle));
	m_position.z = m_limitZ * sin(glm::radians(m_angle));

	m_direction.x = -sin(glm::radians(m_angle));
	m_direction.z = cos(glm::radians(m_angle));
	m_direction = glm::normalize(m_direction);
}

void Fish::draw(std::unique_ptr<Shader> &Shader)
{
	
	float angle = glm::atan(m_direction.x, m_direction.z);  // Rotation on Y axis
	glm::mat4 m_mat = glm::mat4(1.0f);
	m_mat = glm::translate(m_mat, m_position);
	m_mat = glm::rotate(m_mat, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	m_mat = glm::scale(m_mat, m_scale);

	Shader->use();
	Shader->setMat4("model", m_mat);
	m_model.Draw(*Shader);
}

glm::vec3 Fish::getPosition()
{
	return m_position;
}

void Fish::setPosition(const glm::vec3& position)
{
	m_position = position;
}




