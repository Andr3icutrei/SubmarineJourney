#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <GL/glew.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include "shader.h"
#include "ICamera.h"

enum Dir
{
	NONE,
	FORWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STOP
};

class SubmarineCamera : public ICamera
{
public:
	//default camera values
	const float m_zNEAR = 0.1f;
	const float m_zFAR = 500.f;
	const float m_YAW = -90.0f;
	const float m_PITCH = 0.0f;
	const float m_FOV = 75.0f;


	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraOffset;

	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraRight;

	glm::vec3 m_worldUp;

	glm::mat4 m_projectionMatrix;

	float m_yaw;
	float m_pitch;
	float m_rotationSpeed;
	float m_movementSpeed;
	float m_fov;
	float m_znear;
	float m_zfar;

	int m_height;
	int m_width;

	SubmarineCamera(int newHeight, int newWidth, glm::vec3 position);

	void updateCamera(glm::vec3 position, glm::vec3 forwardDirection, float newYaw, float newPitch);
	void Reshape(int windowWidth, int windowHeight) override;
	float getYaw();
	float getPitch();
	glm::mat4 getViewMatrix() const override;
	glm::mat4 getProjectionMatrix() const override;
	glm::vec3 getDirectionVector();
	glm::vec3 getPosition() const override;
private:
	void updateCameraVectors();
};

#endif