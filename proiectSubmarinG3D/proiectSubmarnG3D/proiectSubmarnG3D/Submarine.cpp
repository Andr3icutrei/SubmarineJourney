#include "Submarine.h"

Submarine::Submarine(std::string fileName)
	: submarineModel(1.0f),
	yaw(-90.0f),
	pitch(0.0f),
	roll(0.0f),
	movementSpeed(10.0f),
	submarineScale(0.4f),
	submarinePosition(0.0f),
	m_model(fileName,false),
	m_MAX_SPEED{14.f},
	m_ACCELERATION{2.f},
	m_DECELERATION{1.5f}
{

	updateForwardDirection();
	updateSubmarineDirection();
}

Submarine::Submarine(const Submarine& other):
	submarineModel(other.submarineModel),
	submarinePosition(other.submarinePosition),
	forwardDirection(other.forwardDirection),
	submarineScale(other.submarineScale),
	yaw(other.yaw),
	pitch(other.pitch),
	roll(other.roll),
	movementSpeed(other.movementSpeed),
	m_model{other.m_model},
	m_MAX_SPEED{other.m_MAX_SPEED},
	m_ACCELERATION{other.m_ACCELERATION},
	m_DECELERATION{other.m_DECELERATION}
{
}

Submarine& Submarine::operator=(const Submarine& other)
{
	if (this != &other) {
		submarineModel = other.submarineModel;
		submarinePosition = other.submarinePosition;
		forwardDirection = other.forwardDirection;
		submarineScale = other.submarineScale;
		yaw = other.yaw;
		pitch = other.pitch;
		roll = other.roll;
		movementSpeed = other.movementSpeed;
	}
	return *this;
}

Submarine& Submarine::operator=(Submarine&& other) noexcept
{
	if (this != &other) {

		submarineModel = std::move(other.submarineModel);
		submarinePosition = std::move(other.submarinePosition);
		forwardDirection = std::move(other.forwardDirection);
		submarineScale = std::move(other.submarineScale);
		yaw = other.yaw;
		pitch = other.pitch;
		roll = other.roll;
		movementSpeed = other.movementSpeed;

		other.yaw = 0.0f;
		other.pitch = 0.0f;
		other.roll = 0.0f;
		other.movementSpeed = 0.0f;
	}
	return *this;
}

void Submarine::updateSubmarine(Dir dir, double dt, Shader& shader, bool surface, bool bottom)
{
	float velocity=0.f;

    sideTilt(dir);

    if (dir == Dir::FORWARD) {
        movementSpeed += m_ACCELERATION * dt;
        if (movementSpeed > m_MAX_SPEED) {
            movementSpeed = m_MAX_SPEED; 
        }
        velocity = (float)dt * movementSpeed;
        submarinePosition += forwardDirection * velocity;
    } else if (dir == Dir::STOP) {
        movementSpeed -= m_DECELERATION * dt;
        if (movementSpeed < 0.0f) {
            movementSpeed = 0.0f;
        }
        if (movementSpeed > 0.0f) {
            velocity = (float)dt * movementSpeed;
            submarinePosition += forwardDirection * velocity;
        }
    }

    if (dir == Dir::RIGHT) {
		roll -= 0.2f;

		if (roll <= -20.0f)
			roll = -20.0f;

		yaw += 0.2f;
    }
    if (dir == Dir::LEFT) {
		roll += 0.2f;

		if (roll >= 20.0f)
			roll = 20.0f;

		yaw -= 0.2f;
    }
    if (dir == Dir::UP) {
        if (pitch <= 20.0f) pitch += 0.05f;
        if (pitch >= 20.0f) pitch = 20.0f;
    }
    if (dir == Dir::DOWN) {
        if (pitch >= -20.0f) pitch -= 0.05f;
        if (pitch <= -20.0f) pitch = -20.0f;
    }
	
    if ((surface && pitch >= 0.0f) || (bottom && pitch <= 0.0f)) {
        updateDirection();
    } else {
        updateForwardDirection();
    }

    updateSubmarineDirection();
    draw(shader);
}


glm::mat4 Submarine::getModel()
{
	return submarineModel;
}

glm::vec3 Submarine::getPosition()
{
	return submarinePosition;
}

glm::vec3 Submarine::getForwardDirection()
{
	return forwardDirection;
}

float Submarine::getYaw()
{
	return yaw;
}

float Submarine::getPitch()
{
	return pitch;
}

void Submarine::draw(Shader& shader)
{
	m_model.Draw(shader);
}

void Submarine::updateForwardDirection()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forwardDirection = glm::normalize(direction);
}

void Submarine::updateDirection()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(0.0f));
	direction.y = sin(glm::radians(0.0f));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(0.0f));

	forwardDirection = glm::normalize(direction);
}

void Submarine::updateSubmarineDirection()
{
	submarineModel = glm::mat4(1.0f);
	submarineModel = glm::translate(submarineModel, submarinePosition);

	submarineModel = glm::rotate(submarineModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	submarineModel = glm::rotate(submarineModel, glm::radians(yaw), glm::vec3(0.0f, -1.0f, 0.0f));
	submarineModel = glm::rotate(submarineModel, glm::radians(pitch), glm::vec3(-1.0f, 0.0f, 0.0f));
	submarineModel = glm::rotate(submarineModel, glm::radians(roll), glm::vec3(0.0f, 0.0f, -1.0f));

	submarineModel = glm::scale(submarineModel, submarineScale);
}

void Submarine::sideTilt(Dir dir)
{
	if (dir != Dir::LEFT && dir != Dir::RIGHT && keyState[GLFW_KEY_W]==false && roll != 0.0f)
	{
		float tilt;
		if (roll < 0.0f)
			tilt = +0.1f;
		else
			tilt = -0.1f;

		roll += tilt;
	}
}
