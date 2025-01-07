#include "Fishes.h"

Fish::Fish(const std::string& modelPath, glm::vec3 startPosition, glm::vec3 scale, float speed, float limitX, float limitZ,float angle)
	: m_model(modelPath, false),
	m_position(startPosition),
	m_scale(scale),
	m_direction(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_speed(speed),
	m_limitX(limitX),
	m_limitZ(limitZ),
	m_angle(angle)
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
}

void Fish::draw(Shader& Shader)
{
    float angle = glm::atan(m_position.x, m_position.z)-90.f;

    m_mat = glm::mat4(1.0f);
    m_mat = glm::translate(m_mat, m_position);    

    m_mat = glm::rotate(m_mat, angle, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate around Y-axis

    // Scale the model
    m_mat = glm::scale(m_mat, m_scale);

    Shader.use();
    Shader.setMat4("model", m_mat);
    m_model.Draw(Shader);
}

glm::vec3 Fish::getPosition()
{
	return m_position;  
}

void Fish::setPosition(const glm::vec3& position)
{
	m_position = position;  
}
