#include "LightSource.h"

void LightSource::rotate(double deltaTime,Shader& Shader)
{
	m_rotateAngle += m_rotateSpeed * deltaTime;
	if (m_rotateAngle > 360.f)
		m_rotateAngle -= 360.f;

	m_rotateAngle += 0.001f;
	Shader.use();
	m_mat=glm::mat4(1.0f);
	m_mat=glm::translate(m_mat, glm::vec3(-3.0f, 4.0f, -10.0f));
	m_mat=glm::rotate(m_mat, glm::radians(m_rotateAngle), glm::vec3(0.0f, 0.5f, 0.0f));
	m_mat = glm::scale(m_mat, m_scale);
	Shader.setMat4("model", m_mat);
	m_model.Draw(Shader);
}

void LightSource::appear(Shader& Shader)
{
	Shader.use();
	m_mat=glm::translate(m_mat, glm::vec3(-3.0f, 4.0f, 0.0f));
	m_mat = glm::scale(m_mat, m_scale);
	Shader.setMat4("model", m_mat);
	m_model.Draw(Shader);
}

LightSource::LightSource(std::string& fileName, Shader& Shader,glm::vec3 scale) :
	m_path{fileName} ,
	m_model{fileName,false},
	m_mat{glm::mat4(1.0f)},
	m_rotateAngle{0.f},
	m_rotateSpeed{10.f},
	m_scale{scale}
{
	appear(Shader);
}

void LightSource::SetModelMatrix(glm::mat4 modelMatrix)
{
	m_mat = modelMatrix;
}

glm::mat4& LightSource::GetModelMatrix()
{
	return m_mat;
}
