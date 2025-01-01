#pragma once
#include "glm.hpp"

class IObject
{
public:
	virtual void setModelMatrix(glm::mat4 modelMatrix) = 0;
	virtual glm::mat4& getModelMatrix() = 0;
};

