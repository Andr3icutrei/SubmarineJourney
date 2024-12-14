#ifndef SUBMARINE_CLASS_H
#define SUBMARINE_CLASS_H

#include <GL/glew.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include "shader.h"
#include "Camera.h"
#include <queue>

class Submarine
{
public:
	Submarine();
	void updateSubmarine(Dir dir, double dt);
	glm::mat4 getModel();
	glm::vec3 getPosition();
	glm::vec3 getForwardDirection();
	float getYaw();
	float getPitch();

private:
	glm::mat4 submarineModel;
	glm::vec3 submarinePosition;
	glm::vec3 forwardDirection;
	glm::vec3 submarineScale;
	float yaw;
	float pitch;
	float roll;
	float movementSpeed;

	void updateForwardDirection();
	void updateSubmarineDirection();
	void sideTilt(Dir dir);
};

#endif