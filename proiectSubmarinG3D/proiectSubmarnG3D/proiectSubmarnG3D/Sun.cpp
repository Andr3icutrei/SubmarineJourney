#include "Sun.h"

void Sun::makeSunRotate(double deltaTime,Shader& lightingWithTextureShader)
{
	m_rotateAngle += m_rotateSpeed * deltaTime;
	if (m_rotateAngle > 360.f)
		m_rotateAngle -= 360.f;

	m_rotateAngle += 0.001f;

	m_mat=glm::mat4(1.0f);
	m_mat=glm::translate(m_mat, glm::vec3(-3.0f, 4.0f, 0.0f));
	m_mat=glm::rotate(m_mat, glm::radians(m_rotateAngle), glm::vec3(0.0f, 0.5f, 0.0f));
	m_mat = glm::scale(m_mat, m_scaleFactors);
	lightingWithTextureShader.setMat4("model", m_mat);
	m_model.Draw(lightingWithTextureShader);
}

void Sun::makeSunAppear(Shader& lightingWithTextureShader)
{
	m_mat=glm::translate(m_mat, glm::vec3(-3.0f, 4.0f, 0.0f));
	m_mat = glm::scale(m_mat, m_scaleFactors);
	lightingWithTextureShader.setMat4("model", m_mat);
	m_model.Draw(lightingWithTextureShader);
}

Sun::Sun(std::string& fileName, Shader& lightingWithTextureShader) :
	m_path{fileName} ,
	m_model{fileName,false},
	m_mat{glm::mat4(1.0f)},
	m_scaleFactors{ glm::vec3(8.0f, 8.0f, 1.0f)},
	m_rotateAngle{0.f},
	m_rotateSpeed{10.f}
{
	
	makeSunAppear(lightingWithTextureShader);
}

void Sun::SetModelMatrix(glm::mat4 modelMatrix)
{
	m_mat = modelMatrix;
}

glm::mat4& Sun::GetModelMatrix() 
{
	return m_mat;
}
