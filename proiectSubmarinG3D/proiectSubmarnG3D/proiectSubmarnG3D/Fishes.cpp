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
    // Update the angle of movement along the ellipse
    m_angle += m_speed * deltaTime;
    if (m_angle > 360.0f)
        m_angle -= 360.0f;

    // Update position along the ellipse
    m_position.x = m_limitX * cos(glm::radians(m_angle));
    m_position.z = m_limitZ * sin(glm::radians(m_angle));

    // Direction vector pointing along the tangent to the ellipse (facing the trajectory)
    m_direction.x = -sin(glm::radians(m_angle));  // Direction along X (reversed)
    m_direction.z = cos(glm::radians(m_angle));  // Direction along Z (reversed)
    m_direction = glm::normalize(m_direction);    // Normalize the direction vector

    if (m_angle < 180.0f) {
        // Reverse direction if passed halfway
        m_direction = -m_direction;
    }

    // Rotate the direction vector by 90 degrees counterclockwise (or clockwise)
    // Counterclockwise (left):
    float rotatedX = m_direction.x;   // Swap and negate the x-component for counterclockwise
    float rotatedZ = -m_direction.z;  // Swap and negate the z-component for counterclockwise

    // Update the rotated direction
    m_rotatedDirection = glm::vec3(rotatedX, 0.0f, rotatedZ);
}

void Fish::draw(std::unique_ptr<Shader>& Shader)
{
    // Get the angle of the rotated direction vector to determine fish's orientation
    float angle = glm::atan(m_rotatedDirection.z, m_rotatedDirection.x);  // Get the angle of the rotated direction

    glm::mat4 m_mat = glm::mat4(1.0f);
    m_mat = glm::translate(m_mat, m_position);    
    
    float rightAngle;
    if (m_angle < 180.f)
        rightAngle = -90.f;
    else
        rightAngle = 90.f;

    // Apply the rotation to the fish model (rotate by the calculated angle)
    m_mat = glm::rotate(m_mat, angle, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate around Y-axis

    // Scale the model
    m_mat = glm::scale(m_mat, m_scale);

    // Pass the final model matrix to the shader
    Shader->use();
    Shader->setMat4("model", m_mat);
    m_model.Draw(*Shader);
}

glm::vec3 Fish::getPosition()
{
	return m_position;  
}

void Fish::setPosition(const glm::vec3& position)
{
	m_position = position;  
}
