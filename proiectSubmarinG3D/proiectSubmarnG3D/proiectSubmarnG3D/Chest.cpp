#include "Chest.h"

Chest::Chest(std::string filePath) :
	m_model{ filePath,false },
	m_modelMatrix{ glm::mat4(1.f) }
{
}

void Chest::draw(Shader& shader)
{
	m_model.Draw(shader);
}

void Chest::appear(glm::vec3 position, glm::vec3 scale)
{
	m_modelMatrix = glm::translate(m_modelMatrix, position);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(240.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, scale);

}


