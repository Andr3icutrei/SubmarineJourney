#include "LightSource.h"

void LightSource::rotate(double deltaTime,std::unique_ptr<Shader>& Shader,const glm::mat4& viewMatrix)
{
	m_rotateAngle += m_rotateSpeed * deltaTime;
	if (m_rotateAngle > 360.f)
		m_rotateAngle -= 360.f;

	m_rotateAngle += 0.001f;

	m_mat=glm::mat4(1.0f);

	m_mat=glm::translate(m_mat, m_position);

	m_mat=glm::rotate(m_mat, glm::radians(m_rotateAngle), glm::vec3(0.0f, 0.5f, 0.0f));

	m_mat = glm::scale(m_mat, m_scale);

	glm::vec4 transformedPosition = m_mat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_position = glm::vec3(transformedPosition);

	glm::vec3 lightPosInViewSpace = glm::vec3(viewMatrix * glm::vec4(m_position, 1.0f));
	Shader->SetVec3("lightPos", lightPosInViewSpace);

	Shader->setMat4("model", m_mat);
}

void LightSource::appear(std::unique_ptr<Shader>& Shader)
{
	m_mat=glm::translate(m_mat, m_position);
	m_mat = glm::scale(m_mat, m_scale);
	Shader->setMat4("model", m_mat);
	m_model.Draw(*Shader);
}

void LightSource::draw(std::unique_ptr<Shader>& Shader)
{
	m_model.Draw(*Shader);
}

LightSource::LightSource(std::string& fileName, std::unique_ptr<Shader>& Shader,glm::vec3 scale) :
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
