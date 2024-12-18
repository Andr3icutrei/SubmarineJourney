#pragma once
#include "Model.h"
#include "glm.hpp"
#include "Shader.h"
#include "IObject.h"
#include <fstream>
#include <sstream>

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
	glm::vec3 m_lightColor;
	glm::vec3 m_objectColor;
public:
	LightSource(std::string& fileName ,std::unique_ptr<Shader>& Shader,glm::vec3 scale);

	void rotate(double deltaTime, std::unique_ptr<Shader>& Shader, const glm::mat4& viewMatrix);

	void appear(std::unique_ptr<Shader>& Shader);

	void draw(std::unique_ptr<Shader>& shader);

	glm::vec3 getColor() const;

	void setColor(glm::vec3 color);

	void SetModelMatrix(glm::mat4 modelMatrix) override;

	glm::mat4& GetModelMatrix() override;

	void SetPosition(glm::vec3 pos) { m_position = pos; }

	Model& getModel(){return m_model;}

	void setModel(const Model& model){m_model = model;}

	glm::mat4& getModelMatrix(){return m_mat;}

	void setModelMatrix(const glm::mat4& modelMatrix){m_mat = modelMatrix;}

	std::string getPath() const{return m_path;}

	void setPath(const std::string& path){m_path = path;}

	float getRotateAngle() const{return m_rotateAngle;}

	void setRotateAngle(float rotateAngle){m_rotateAngle = rotateAngle;}

	float getRotateSpeed() const{return m_rotateSpeed;}

	void setRotateSpeed(float rotateSpeed){m_rotateSpeed = rotateSpeed;}

	glm::vec3 getPosition() const{return m_position;}

	void setPosition(const glm::vec3& position){	m_position = position;}

	glm::vec3 getScale() const{	return m_scale;}

	void setScale(const glm::vec3& scale){	m_scale = scale;}

	glm::vec3 getLightColor() const { return m_lightColor; }

	void setLightColor(const glm::vec3& lightColor) { m_lightColor = lightColor; }

	
};

