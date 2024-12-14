#include "Submarine.h"

Submarine::Submarine()
	: submarineModel(1.0f),
	yaw(-90.0f),
	pitch(0.0f),
	roll(0.0f),
	movementSpeed(100.0f),
	submarineScale(0.2f),
	submarinePosition(0.0f)
{
	updateForwardDirection();
	updateSubmarineDirection();
}

void Submarine::updateSubmarine(Dir dir, double dt)
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
	case FORWARD_LEFT: {
		roll += 1.0f;

		if (roll >= 20.0f)
			roll = 20.0f;

		submarinePosition += forwardDirection * velocity;
		break;
	}
	case FORWARD_RIGHT: {
		roll -= 1.0f;

		if (roll <= -20.0f)
			roll = -20.0f;

		submarinePosition += forwardDirection * velocity;
		break;
	}
	}

	updateForwardDirection();

	updateSubmarineDirection();
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

void Submarine::updateForwardDirection()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

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

	submarineModel = glm::scale(submarineModel, glm::vec3(0.2f));
}

void Submarine::sideTilt(Dir dir)
{
	if (dir != Dir::LEFT && dir != Dir::FORWARD_LEFT &&
		dir != Dir::RIGHT && dir != Dir::FORWARD_RIGHT && roll != 0.0f)
	{
		float tilt;
		if (roll < 0.0f)
			tilt = +0.5f;
		else
			tilt = -0.5f;

		roll += tilt;
	}
}
