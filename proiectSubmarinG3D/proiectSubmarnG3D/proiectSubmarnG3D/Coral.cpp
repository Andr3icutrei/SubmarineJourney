#include "Coral.h"

Coral::Coral(const std::string& modelPath, glm::vec3 position, glm::vec3 scale)
: m_model(modelPath, false),
m_position(position),
m_scale(scale)
{
	m_mat = glm::translate(glm::mat4(1.0f), m_position);
	m_mat = glm::scale(m_mat, m_scale);
}

void Coral::draw(std::unique_ptr<Shader>& shader)
{
	shader->use();
	shader->setMat4("model", m_mat);
	m_model.Draw(*shader);
}

void Coral::setPosition(const glm::vec3& position)
{
	m_position = position;
	m_mat = glm::translate(glm::mat4(1.0f), m_position);
	m_mat = glm::scale(m_mat, m_scale);
}

glm::vec3 Coral::getPosition()
{
	return m_position;
}

void Coral::setScale(const glm::vec3& scale)
{
	m_scale = scale;
	m_mat = glm::translate(glm::mat4(1.0f), m_position);
	m_mat = glm::scale(m_mat, m_scale);
}

glm::vec3 Coral::getScale()
{
	return m_scale;
}

