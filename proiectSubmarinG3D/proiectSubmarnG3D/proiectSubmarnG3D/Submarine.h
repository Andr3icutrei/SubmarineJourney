#pragma once
#include <GL/glew.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include "shader.h"
#include "SubmarineCamera.h"
#include "Model.h"

#include <memory>
#include <string>

class Submarine
{
public:
	Submarine(std::string fileName);
	Submarine(const Submarine& other);
	Submarine& operator=(const Submarine& other);
	Submarine(Submarine&& other) noexcept;
	Submarine& operator=(Submarine&& other) noexcept;

	void updateSubmarine(Dir dir, double dt, Shader& shader, bool surface);
	glm::mat4 getModel();
	glm::vec3 getPosition();
	glm::vec3 getForwardDirection();
	float getYaw();
	float getPitch();

	void draw(Shader& shader);

private:
	glm::mat4 submarineModel;
	glm::vec3 submarinePosition;
	glm::vec3 forwardDirection;
	glm::vec3 submarineScale;
	float yaw;
	float pitch;
	float roll;
	float movementSpeed;
	Model m_model;

	void updateForwardDirection();
	void updateForwardDirectionSurface();
	void updateSubmarineDirection();
	void sideTilt(Dir dir);
};
