#include "SpongebobHouse.h"

SpongebobHouse::SpongebobHouse(std::string filename) :
	m_model{ filename,false },
	m_modelMatrix{ glm::mat4(1.f) }
{
}

void SpongebobHouse::draw(Shader& shader)
{
	m_model.Draw(shader);
}

void SpongebobHouse::appear(glm::vec3 position, glm::vec3 scale)
{
	m_modelMatrix = glm::translate(m_modelMatrix, position);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, scale);

}

