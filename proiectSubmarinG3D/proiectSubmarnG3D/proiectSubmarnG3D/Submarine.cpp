#include "Submarine.h"

Submarine::Submarine(std::string fileName)
	: submarineModel(1.0f),
	yaw(-90.0f),
	pitch(0.0f),
	roll(0.0f),
	movementSpeed(200.0f),
	submarineScale(0.4f),
	submarinePosition(0.0f),
	m_model(fileName,false)
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
	m_model{other.m_model}
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

Submarine::Submarine(Submarine&& other) noexcept: 
	submarineModel(std::move(other.submarineModel)),
	submarinePosition(std::move(other.submarinePosition)),
	forwardDirection(std::move(other.forwardDirection)),
	submarineScale(std::move(other.submarineScale)),
	yaw(other.yaw),
	pitch(other.pitch),
	roll(other.roll),
	movementSpeed(other.movementSpeed),
	m_model{other.m_model}
{
	other.yaw = 0.0f;
	other.pitch = 0.0f;
	other.roll = 0.0f;
	other.movementSpeed = 0.0f;
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

void Submarine::updateSubmarine(Dir dir, double dt, Shader& shader, bool surface)
{
	float velocity = (float)dt * movementSpeed;

	sideTilt(dir);

	switch (dir) {
	case FORWARD: {
		submarinePosition += forwardDirection * velocity;
		break;
	}
	case RIGHT: {
		roll -= 1.0f;

		if (roll <= -20.0f)
			roll = -20.0f;

		yaw += 1.0f;
		break;
	}
	case LEFT: {
		roll += 1.0f;

		if (roll >= 20.0f)
			roll = 20.0f;

		yaw -= 1.0f;
		break;
	}
	case UP: {
		if (pitch <= 20.0f)
			pitch += 0.5f;

		if (pitch >= 20.0f)
			pitch = 20.0f;

		break;
	}
	case DOWN: {
		if (pitch >= -20.0f)
			pitch -= 0.5f;

		if (pitch <= -20.0f)
			pitch = -20.0f;

		break;
	}
	}

	if (surface && pitch >= 0.0f)
		updateForwardDirectionSurface();
	else 
		updateForwardDirection();

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

void Submarine::updateForwardDirectionSurface()
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
	if (dir != Dir::LEFT && dir != Dir::RIGHT && roll != 0.0f)
	{
		float tilt;
		if (roll < 0.0f)
			tilt = +0.5f;
		else
			tilt = -0.5f;

		roll += tilt;
	}
}
