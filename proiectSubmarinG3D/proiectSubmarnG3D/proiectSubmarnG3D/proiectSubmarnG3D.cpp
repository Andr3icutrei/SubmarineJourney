// ViewOBJModel.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <locale>
#include <codecvt>

#include <stdlib.h> // necesare pentru citirea shader-elor
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

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

GLuint ProjMatrixLocation, ViewMatrixLocation, WorldMatrixLocation;
Submarine* submarine = nullptr;

SubmarineCamera submarineCamera(SCR_HEIGHT, SCR_WIDTH, glm::vec3(0.0, 0.0, 3.0));
SideviewCamera sideCamera(glm::vec3(7.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	SCR_WIDTH, SCR_HEIGHT);
ICamera* camera = nullptr;

void Cleanup()
{
	delete camera;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// timing
double deltaTime = 0.0f;	// time between current frame and last frame
double lastFrame = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::UP, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::FORWARD_LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::FORWARD_RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)//O - camera submarinului
	{
		if (SideviewCamera* currentCamera = dynamic_cast<SideviewCamera*>(camera))
		{
			camera = &submarineCamera;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)//P- side view camera
	{
		if (SubmarineCamera* currentCamera = dynamic_cast<SubmarineCamera*>(camera))
		{
			camera = &sideCamera;
		}
	}
	if (SubmarineCamera* currentCamera = dynamic_cast<SubmarineCamera*>(camera))
	{
		currentCamera->updateCamera(submarine->getPosition(), submarine->getForwardDirection(), submarine->getYaw(), submarine->getPitch());
	}
}

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	camera = new SubmarineCamera(submarineCamera);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Submarine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewInit();

	glEnable(GL_DEPTH_TEST);


	//Create submarine	
	submarine = new Submarine();

	glm::vec3 lightPos(0.0f, 2.0f, 1.0f);
	glm::vec3 cubePos(0.0f, 5.0f, 1.0f);

	wchar_t buffer[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, buffer);

	std::wstring executablePath(buffer);
	std::wstring wscurrentPath = executablePath.substr(0, executablePath.find_last_of(L"\\/"));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string currentPath = converter.to_bytes(wscurrentPath);

	Shader lightingShader((currentPath + "\\Shaders\\PhongLight.vs").c_str(), (currentPath + "\\Shaders\\PhongLight.fs").c_str());
	
	Shader lightingWithTextureShader((currentPath + "\\Shaders\\PhongLightWithTexture.vs").c_str(), (currentPath + "\\Shaders\\PhongLightWithTexture.fs").c_str());
	
	Shader lampShader((currentPath + "\\Shaders\\Lamp.vs").c_str(), (currentPath + "\\Shaders\\Lamp.fs").c_str());
	
	Shader waterShader((currentPath+"\\Shaders\\Water.vs").c_str(), (currentPath + "\\Shaders\\Water.fs").c_str());
	std::string strWaterJpgPath = currentPath + "\\x64\\Debug\\water.jpg";
	const char* waterPath{ strWaterJpgPath.c_str()};
	Water water(glm::vec3(0.0f, 1.0f, 3.0f), glm::vec3(10.0f, 10.0f, 10.0f), waterPath);

	glm::mat4 submarineModel = glm::mat4(1.0f);
	std::string submarineFileName = (currentPath + "\\Models\\Submarin\\submarin.obj");
	Model submarineObjModel(submarineFileName, false);

	std::string lightSourcePath = currentPath;

	std::time_t currentTime = std::time(nullptr);
	std::tm* localTime = std::localtime(&currentTime);
	int hour = localTime->tm_hour;

	glm::vec3 lightSourceScale;
	glm::vec3 lightColor;
	if (hour >= 6 && hour <= 18)
	{
		lightColor = glm::vec3(1.0f, 0.95f, 0.6f);//sun light color
		lightSourcePath += "\\Models\\Sun\\sun.obj";
		lightSourceScale = glm::vec3(5.0f, 5.0f, 1.0f);
	}
	else
	{
		lightColor= glm::vec3(0.7f, 0.8f, 1.0f);//moon light color
		lightSourcePath += "\\Models\\Moon\\Moon.obj";
		lightSourceScale = glm::vec3(0.2f, 0.2f, 0.2f);
	}

	glDepthMask(true);
	LightSource lightSource(lightSourcePath,lightingWithTextureShader,lightSourceScale);
	lightSource.setPosition(glm::vec3(-3.0f, 3.0f, -8.0f));

	// render loop	
	while (!glfwWindowShouldClose(window)) {
		// per-frame time logic
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		waterShader.use();
		waterShader.setMat4("view", camera->getViewMatrix());
		waterShader.setMat4("projection", camera->getProjectionMatrix());


		// Draw water
		water.draw(waterShader);

		lightingWithTextureShader.use();
		lightingWithTextureShader.SetVec3("objectColor", 0.5f, 1.0f, 0.31f);
		lightingWithTextureShader.SetVec3("lightColor", lightColor);

		lightingWithTextureShader.SetVec3("viewPos", camera->getPosition());
		lightingWithTextureShader.setInt("texture_diffuse1", 0);

		lightSource.rotate(deltaTime, lightingWithTextureShader, camera->getViewMatrix());
		lightSource.draw(lightingWithTextureShader);

		//std::cout << lightSource.getPosition().x<< " "<<lightSource.getPosition().y<<" "<<
			//lightSource.getPosition().z;
		if (SubmarineCamera* subCam = dynamic_cast<SubmarineCamera*>(camera))
		{
			lightingWithTextureShader.setMat4("projection", subCam->getProjectionMatrix());
			lightingWithTextureShader.setMat4("view", subCam->getViewMatrix());
			lightingWithTextureShader.setMat4("model", submarine->getModel());
		}
		else if (SideviewCamera* sideCam = dynamic_cast<SideviewCamera*>(camera))
		{
			glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
			lightingWithTextureShader.setMat4("projection", projection);
			lightingWithTextureShader.setMat4("view", sideCam->getViewMatrix());
			lightingWithTextureShader.setMat4("model", submarine->getModel());
		}

		submarineObjModel.Draw(lightingWithTextureShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Cleanup();

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	camera->Reshape(width, height);
}