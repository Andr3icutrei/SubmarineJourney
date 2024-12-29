#include "Fishes.h"

Fish::Fish(const std::string& modelPath, glm::vec3 startPosition, glm::vec3 scale, float speed, float limitX, float limitZ)
	: m_model(modelPath, false),
	m_position(startPosition),
	m_scale(scale),
	m_direction(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_speed(speed),
	m_limitX(limitX),
	m_limitZ(limitZ),
	m_angle(0.0f)
{
}

void Fish::update(float deltaTime)
{
	// Update the angle based on the speed and deltaTime.
	m_angle += m_speed * deltaTime;
	if (m_angle > 360.0f)
		m_angle -= 360.0f;

	// Update the position in an elliptical motion on X and Z axes
	m_position.x = m_limitX * cos(glm::radians(m_angle));
	m_position.z = m_limitZ * sin(glm::radians(m_angle));

	// Update the direction based on the angle
	m_direction.x = -sin(glm::radians(m_angle)); // Direction along X
	m_direction.z = cos(glm::radians(m_angle));  // Direction along Z
	m_direction = glm::normalize(m_direction);   // Normalize the direction vector
}

void Fish::draw(std::unique_ptr<Shader>& Shader)
{
	// Calculate the angle for the fish's rotation
	float angle = glm::atan(m_direction.z, m_direction.x); // Corrected angle calculation

	// Create transformation matrix
	glm::mat4 m_mat = glm::mat4(1.0f);
	m_mat = glm::translate(m_mat, m_position);  // Apply translation
	m_mat = glm::rotate(m_mat, angle, glm::vec3(0.0f, 1.0f, 0.0f));  // Apply rotation (yaw)
	m_mat = glm::scale(m_mat, m_scale);  // Apply scaling

	// Set the shader and draw the model
	Shader->use();
	Shader->setMat4("model", m_mat);  // Set the model matrix
	m_model.Draw(*Shader);  // Render the model
}

glm::vec3 Fish::getPosition()
{
	return m_position;  // Return the current position of the fish
}

void Fish::setPosition(const glm::vec3& position)
{
	m_position = position;  // Set a new position for the fish
}
