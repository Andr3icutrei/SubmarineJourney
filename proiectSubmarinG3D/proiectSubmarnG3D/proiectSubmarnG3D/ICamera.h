#pragma once
#include "glm.hpp"

class ICamera
{
public:
	virtual glm::mat4 getViewMatrix() const=0 ;
	virtual ~ICamera() = default;
	virtual glm::vec3 getPosition() const = 0;
	virtual void Reshape(int windowWidth, int windowHeight)=0;
	virtual glm::mat4 getProjectionMatrix() const =0;
};

