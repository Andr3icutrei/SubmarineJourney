#pragma once
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
#include <memory>
#include <random>

#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

#include "Shader.h"
#include "Model.h"
#include "FlyingCube.h"
#include "LightSource.h"
#include "Submarine.h"
#include "SubmarineCamera.h"
#include "SideviewCamera.h"
#include "Water.h"
#include "Skybox.h"
#include "Fishes.h"
#include "Coral.h"
#include "SpongebobHouse.h"
#include "Turtle.h"
#include "Chest.h"

class RunProgram
{
private:
    static RunProgram* instance;

    RunProgram();
    RunProgram(const RunProgram&) = delete;
    RunProgram& operator=(const RunProgram&) = delete;

    const unsigned int m_SCR_WIDTH = 1500;
    const unsigned int m_SCR_HEIGHT = 1000;

    GLFWwindow* window;

    glm::vec3 m_submarinePosition;

    glm::vec3 m_sideCameraPosition;
    glm::vec3 m_sideCameraTarget;
    glm::vec3 m_sideCameraWorldUp;

    GLuint ProjMatrixLocation, ViewMatrixLocation, WorldMatrixLocation;

    std::string m_currentPath;

    glm::vec3 m_lightDir;

    std::shared_ptr<Submarine> m_submarine;
    std::shared_ptr<SubmarineCamera> m_submarineCamera;
    std::shared_ptr<SideviewCamera> m_sideCamera;
    std::shared_ptr<ICamera> m_camera;
    std::shared_ptr<Water> m_water;
    std::shared_ptr<LightSource> m_lightSource;
    std::shared_ptr<Skybox> m_skybox;
    std::vector<std::shared_ptr<Fish>> m_fishes;
    std::vector<std::shared_ptr<Coral>> m_corals;
    std::shared_ptr<SpongebobHouse> m_spongebobHouse;
    std::vector<std::shared_ptr<Turtle>> m_turtles;
    std::shared_ptr<Chest> m_chest;

    std::unique_ptr<Shader> m_objectShader;
    std::unique_ptr<Shader> m_lightSourceShader;
    std::unique_ptr<Shader> m_waterShader;
    std::unique_ptr<Shader> m_skyboxShader;
    std::unique_ptr<Shader> m_shadowShader;

    unsigned int m_shadowMap;
    unsigned int m_shadowFBO;

    glm::mat4 m_lightSpaceMatrix;

    const float m_SHADOW_WIDTH = 1024;
    const float m_SHADOW_HEIGTH = 1024;

    double deltaTime = 0.0f;
    double lastFrame = 0.0f;

    void initializeGL();
    void initializePaths();

    void createWater();
    void createSubmarine();
    void createLightSource();
    void createSkybox();
    void createFish();
    void createCorals();
    void createTurtles();
    void createSpongebobHouse();
    void createChest();

    void initializeCameras();

    void renderWater();
    void renderSubmarine();
    void renderLightSource();
    void renderSkybox();
    void renderFish();
    void renderCorals();
    void renderTurtles();
    void renderSpongebobHouse();
    void renderChest();
    void render();

    float generateRandom(float min, float max);

    void generateShadowMap();
    void generateShadowMapTexture();

    void playMusic();

public:
    // Static method to get the instance of the class
    static RunProgram* getInstance();

    void run();

    //getters
    unsigned int getSCRWidth() const { return m_SCR_WIDTH; }
    unsigned int getSCRHeight() const { return m_SCR_HEIGHT; }

    GLuint getProjMatrixLocation() const { return ProjMatrixLocation; }
    GLuint getViewMatrixLocation() const { return ViewMatrixLocation; }
    GLuint getWorldMatrixLocation() const { return WorldMatrixLocation; }

    std::shared_ptr<Submarine> getSubmarine() { return m_submarine; }
    std::shared_ptr<SubmarineCamera> getSubmarineCamera() { return m_submarineCamera; }
    std::shared_ptr<SideviewCamera> getSideCamera() { return m_sideCamera; }
    std::shared_ptr<ICamera> getCamera() const { return m_camera; }
    std::shared_ptr<Water> getWater() { return m_water; }

    double getDeltaTime() const { return deltaTime; }
    double getLastFrame() const { return lastFrame; }

    Shader& getSubmarineShader() { return *m_objectShader; }

    // Setters
    void setProjMatrixLocation(GLuint value) { ProjMatrixLocation = value; }
    void setViewMatrixLocation(GLuint value) { ViewMatrixLocation = value; }
    void setWorldMatrixLocation(GLuint value) { WorldMatrixLocation = value; }

    void setSubmarine(std::shared_ptr<Submarine> sub) { m_submarine = std::move(sub); }
    void setSubmarineCamera(std::shared_ptr<SubmarineCamera> cam) { m_submarineCamera = std::move(cam); }
    void setSideCamera(std::shared_ptr<SideviewCamera> cam) { m_sideCamera = std::move(cam); }
    void setCamera(std::shared_ptr<ICamera> cam) { m_camera = std::move(cam); }

    void setDeltaTime(double time) { deltaTime = time; }
    void setLastFrame(double time) { lastFrame = time; }

};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window, std::shared_ptr<Submarine> submarine, float deltaTime, bool surface, bool bottom);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
