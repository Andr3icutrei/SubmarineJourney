#pragma once
#include "glm.hpp"

class IObject
{
public:
	virtual void SetModelMatrix(glm::mat4 modelMatrix) = 0;
	virtual glm::mat4& GetModelMatrix() = 0;
};

