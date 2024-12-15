#include "SideviewCamera.h"

SideviewCamera::SideviewCamera(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp, const int width, const int height) :
	m_position{pos},
	m_target{target},
	m_worldUp{worldUp},
	m_fov{60.0f},
	m_nearPlane{0.1f},
	m_farPlane{100.f},
	m_aspectRatio{(float)width/(float)height}
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

void SideviewCamera::Reshape(int windowWidth, int windowHeight)
{
	m_width = windowWidth;
	m_height = windowHeight;

	// define the viewport transformation
	glViewport(0, 0, windowWidth, windowHeight);
}