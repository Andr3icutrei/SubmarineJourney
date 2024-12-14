#pragma once
#include "Model.h"
#include "glm.hpp"
#include "Shader.h"
#include "IObject.h"

class Sun : public IObject
{
private:
	Model m_model;
	glm::mat4 m_mat;
	std::string m_path;
	glm::vec3 m_scaleFactors;
	float m_rotateAngle;
	float m_rotateSpeed;

public:
	Sun(std::string& fileName,Shader& lightingWithTextureShader);

	void makeSunRotate(double deltaTime, Shader& lightingWithTextureShader);
	void makeSunAppear(Shader& lightingWithTextureShader);

	void SetModelMatrix(glm::mat4 modelMatrix) override;

	glm::mat4& GetModelMatrix() override;
};

