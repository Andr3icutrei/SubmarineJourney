#include "SubmarineCamera.h"

SubmarineCamera::SubmarineCamera(int newHeight, int newWidth, glm::vec3 position) :
	m_height(newHeight),
	m_width(newWidth),
	m_cameraPosition(position),
	m_cameraOffset(0.0f, 0.3f, 3.2f),
	m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_yaw(m_YAW),
	m_pitch(m_PITCH),
	m_rotationSpeed(10000.0f),
	m_movementSpeed(100.0f),
	m_fov(m_FOV),
	m_znear(m_zNEAR),
	m_zfar(m_zFAR),
	m_cameraFront(glm::vec3(0.0f, 0.0f, -1.0f))
{
	updateCameraVectors();
}


void SubmarineCamera::updateCamera(glm::vec3 position, glm::vec3 forwardDirection, float newYaw, float newPitch)
{
	m_cameraPosition = position - forwardDirection * m_cameraOffset.z + glm::vec3(0.0f, m_cameraOffset.y, 0.0f);

	m_yaw = newYaw;
	m_pitch = newPitch;

	updateCameraVectors();
}

glm::mat4 SubmarineCamera::getViewMatrix() const 
{
	return glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
}

glm::mat4 SubmarineCamera::getProjectionMatrix() const 
{
	glm::mat4 Proj = glm::mat4(1);

	float aspectRatio = ((float)(m_width)) / m_height;
	Proj = glm::perspective(glm::radians(m_fov), aspectRatio, m_znear, m_zfar);

	return Proj;
}

glm::vec3 SubmarineCamera::getDirectionVector()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	return direction;
}

glm::vec3 SubmarineCamera::getPosition() const
{
	return m_cameraPosition;
}

void SubmarineCamera::updateCameraVectors()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_cameraFront = glm::normalize(direction);
	m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_worldUp));
	m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
}

void SubmarineCamera::Reshape(int windowWidth, int windowHeight)
{
	m_width = windowWidth;
	m_height = windowHeight;

	glViewport(0, 0, windowWidth, windowHeight);
}

float SubmarineCamera::getYaw()
{
	return m_yaw;
}

float SubmarineCamera::getPitch()
{
	return m_pitch;
}
