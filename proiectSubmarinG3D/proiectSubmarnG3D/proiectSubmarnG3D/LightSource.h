#pragma once
#include "Model.h"
#include "glm.hpp"
#include "Shader.h"
#include "IObject.h"

class LightSource : public IObject
{
private:
	Model m_model;
	glm::mat4 m_mat;
	std::string m_path;
	float m_rotateAngle;
	float m_rotateSpeed;
	glm::vec3 m_position;
	glm::vec3 m_scale;
public:
	LightSource(std::string& fileName,Shader& Shader,glm::vec3 scale);

	void rotate(double deltaTime, Shader& Shader);
	void appear(Shader& Shader);

	void SetModelMatrix(glm::mat4 modelMatrix) override;

	glm::mat4& GetModelMatrix() override;
};

