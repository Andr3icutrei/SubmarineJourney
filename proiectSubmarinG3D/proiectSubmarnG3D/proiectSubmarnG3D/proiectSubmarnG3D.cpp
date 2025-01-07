
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <locale>
#include <codecvt>

#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

#include <GL/glew.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glfw3.h>

#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "Model.h"
#include "FlyingCube.h"
#include "LightSource.h"
#include "Submarine.h"
#include "SubmarineCamera.h"
#include "SideviewCamera.h"
#include "Water.h"
#include "RunProgram.h"

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

RunProgram* RunProgram::instance = nullptr;

int main()
{
	RunProgram* rp = RunProgram::getInstance();
	rp->run();
}