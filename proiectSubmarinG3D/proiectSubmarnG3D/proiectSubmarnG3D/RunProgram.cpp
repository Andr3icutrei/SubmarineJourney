#include "RunProgram.h"

RunProgram::RunProgram() {
}

RunProgram* RunProgram::getInstance()
{
	if (instance == nullptr) 
	{
		instance = new RunProgram();
	}
	return instance;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

void RunProgram::run()
{
	initializeGL();
	initializeCameras();
	initializePaths();
	createLightSource();
	createSubmarine();
	createWater();
	createFishes();
	createSkybox();
	render();
}

void RunProgram::initializeCameras()
{
	m_submarinePosition = glm::vec3(0.0, 0.0, 3.0);
	m_submarineCamera =std::make_shared<SubmarineCamera>(m_SCR_HEIGHT, m_SCR_WIDTH,m_submarinePosition);

	m_sideCameraPosition = glm::vec3(7.0f, 3.0f, 0.0f);
	m_sideCameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	m_sideCameraWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	m_sideCamera =std::make_shared<SideviewCamera>(m_sideCameraPosition,m_sideCameraTarget, m_sideCameraWorldUp,
		m_SCR_WIDTH, m_SCR_HEIGHT);

	m_camera = m_submarineCamera;
}

void RunProgram::render()
{
	while (!glfwWindowShouldClose(window)) {
		glm::vec3 lightDir=  glm::normalize(-m_lightSource->getPosition());
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthMask(GL_FALSE);

		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 15.0f, 35.0f)); // Scale with a smaller value for Y
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 7.0f, 0.0f));
		glm::mat4 modelMatrix = translateMatrix * scaleMatrix;
		m_skyboxShader->use();
		m_skyboxShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_skyboxShader->SetVec3("lightDir", lightDir);
		m_skyboxShader->setMat4("view", m_camera->getViewMatrix());
		m_skyboxShader->setMat4("projection",m_camera->getProjectionMatrix());
		m_skyboxShader->setMat4("model", modelMatrix);
		m_skybox->draw(*m_skyboxShader);

		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);

		m_lightSourceShader->use();
		m_lightSourceShader->setFloat("shininess", 0.8f);
		m_lightSourceShader->setMat4("model", m_lightSource->GetModelMatrix());
		m_lightSourceShader->setMat4("view", m_camera->getViewMatrix());
		m_lightSourceShader->setMat4("projection", m_camera->getProjectionMatrix());
		m_lightSourceShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_lightSourceShader->setInt("texture_diffuse1", 0);
		m_lightSource->rotate(deltaTime, m_lightSourceShader, m_camera->getViewMatrix());
		m_lightSource->draw(m_lightSourceShader);

		m_submarineShader->use();
		//glm::vec3 lightDir = glm::normalize( m_submarine->getPosition()- m_lightSource->getPosition());
		m_submarineShader->SetVec3("lightDir", lightDir);
		m_submarineShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_submarineShader->SetVec3("viewPos", m_camera->getPosition()); 
		m_submarineShader->setMat4("projection", m_camera->getProjectionMatrix());
		m_submarineShader->setMat4("view", m_camera->getViewMatrix());
		m_submarineShader->setMat4("model", m_submarine->getModel());
		m_submarineShader->setInt("texture_diffuse1", 0);
		m_submarine->draw(*m_submarineShader);

		for (auto& fish : m_fishes)
		{
			fish->update(deltaTime); 
			fish->draw(m_submarineShader);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		m_waterShader->use();
		m_waterShader->SetVec3("lightDir", lightDir);
		m_waterShader->setFloat("time", glfwGetTime());
		m_waterShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_waterShader->setMat4("view", m_camera->getViewMatrix());
		m_waterShader->setMat4("projection", m_camera->getProjectionMatrix());
		m_waterShader->SetVec3("lightColor", m_lightSource->getLightColor());
		m_water->draw(*m_waterShader);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();
}

float RunProgram::generateRandom(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Define a uniform distribution for integers
	std::uniform_int_distribution<> uniformDist(min, max);

	float rand = uniformDist(gen);
	return rand;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	RunProgram* instance = RunProgram::getInstance();
	instance->getCamera()->Reshape(width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	RunProgram* instance = RunProgram::getInstance();
	float deltaTime = instance->getDeltaTime();
	std::shared_ptr<Submarine> submarine = instance->getSubmarine();
	std::shared_ptr<Water> water = instance->getWater();

	bool surface = false;

	if (submarine->getPosition().y >= 0.0f)
		surface = true;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		RunProgram::getInstance()->getSubmarine()->updateSubmarine(Dir::LEFT, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::RIGHT, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::UP, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::DOWN, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		submarine->updateSubmarine(Dir::FORWARD, deltaTime, RunProgram::getInstance()->getSubmarineShader(), surface);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	std::shared_ptr<ICamera> camera = instance->getCamera();
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)//O - camera submarinului
	{
		instance->setCamera( instance->getSubmarineCamera());
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)//P- side view camera
	{
		instance->setCamera(instance->getSideCamera());
	}

	if (std::shared_ptr<SubmarineCamera> currentCamera = std::dynamic_pointer_cast<SubmarineCamera>(camera))
	{
		currentCamera->updateCamera(submarine->getPosition(), submarine->getForwardDirection(), submarine->getYaw(), submarine->getPitch());
	}
}

void RunProgram::initializeGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(m_SCR_WIDTH, m_SCR_HEIGHT, "Submarine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RunProgram::initializePaths()
{
	wchar_t buffer[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, buffer);

	std::wstring executablePath(buffer);
	std::wstring wscurrentPath = executablePath.substr(0, executablePath.find_last_of(L"\\/"));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	m_currentPath = converter.to_bytes(wscurrentPath);

	m_submarineShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\Object.vs").c_str(), (m_currentPath + "\\Shaders\\Object.fs").c_str());
	m_lightSourceShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\LightSource.vs").c_str(), (m_currentPath + "\\Shaders\\LightSource.fs").c_str());
	m_waterShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\Water.vs").c_str(), (m_currentPath + "\\Shaders\\Water.fs").c_str());
	m_skyboxShader = std::make_unique<Shader>((m_currentPath + "\\Shaders\\Skybox.vs").c_str(), (m_currentPath + "\\Shaders\\Skybox.fs").c_str());
}

void RunProgram::createWater()
{
	std::string strWaterJpgPath = m_currentPath + "\\x64\\Debug\\water.jpg";
	const char* waterPath{ strWaterJpgPath.c_str() };

	std::string strSandJpgPath = m_currentPath + "\\x64\\Debug\\sand.jpg";
	const char* sandPath{ strSandJpgPath.c_str() };

	m_water = std::make_shared<Water>(glm::vec3(0.0f, -4.0f, 3.0f), glm::vec3(80.0f, 8.0f, 80.0f), waterPath, sandPath);
}

void RunProgram::createSubmarine()
{
	std::string submarineFileName = (m_currentPath + "\\Models\\Submarin\\submarin.obj");
	m_submarine = std::make_shared<Submarine>(submarineFileName);
}

void RunProgram::createLightSource()
{
	std::string lightSourcePath = m_currentPath;

	std::time_t currentTime = std::time(nullptr);
	std::tm* localTime = std::localtime(&currentTime);
	int hour = localTime->tm_hour;

	glm::vec3 lightSourceScale=glm::vec3(1.0f);
	glm::vec3 lightColor;
	std::string mtlPath;
	if (hour >= 6 && hour <= 18)
	{
		lightColor = (glm::vec3(1.0f, 0.95f, 1.f));//sun light color
		lightSourcePath += "\\Models\\Sun\\sun.obj";
		lightSourceScale = (glm::vec3(5.0f, 5.0f, 1.0f));
	}
	else
	{
		lightColor=(glm::vec3(0.6f, 0.6f, 1.0f));//moon light color
		lightSourcePath += "\\Models\\Moon\\Moon.obj";
		lightSourceScale=(glm::vec3(0.2f, 0.2f, 0.2f));
	}

	m_lightSource=std::make_shared<LightSource>(lightSourcePath,m_lightSourceShader, lightSourceScale);
	m_lightSource->setPosition(glm::vec3(-3.0f, 4.0f, -8.0f));
	m_lightSource->setLightColor(lightColor);
}

void RunProgram::createSkybox()
{
	std::string skyPath = m_currentPath + "\\x64\\Debug\\sky.jpg";
	m_skybox = std::make_shared<Skybox>(skyPath.c_str());
}

void RunProgram::createFishes()
{
    std::string fishPath = m_currentPath + "\\Models\\Fish\\fish.obj";

    const int FishCount = 7;
    std::vector<float> linearFishSpeeds(FishCount, 6.f);
    std::vector<float> linearFishHeights(FishCount);
    std::vector<float> movementLimitsX(FishCount); // Radius on X axis (ellipse)
    std::vector<float> movementLimitsZ(FishCount); // Radius on Z axis (ellipse)

    const int waterSurface = m_water->getSurface(); // water max
    const int waterBottom = m_water->getBottom(); // water min
    float maxRadius = m_water->getDistanceFromCenter(); // max radius to spawn
    float startPositionToSpawn = 0.f;

    for (int i = 0; i < FishCount; ++i)
    {
        movementLimitsX[i] = generateRandom(1.0f, maxRadius); 
        movementLimitsZ[i] = generateRandom(1.0f, maxRadius);
    }

	linearFishHeights[0]=-4.f;
	for (int i = 1; i < FishCount; ++i)
	{
		linearFishHeights[i] = linearFishHeights[i - 1] - 1.f;
	}

    for (int i = 0; i < FishCount; ++i)
    {
        float randomX = generateRandom(-movementLimitsX[i], movementLimitsX[i]);
        float randomZ = generateRandom(-movementLimitsZ[i], movementLimitsZ[i]);

        std::cout << "Fish " << i << " position: X=" << randomX << ", Y=" << linearFishHeights[i] << ", Z=" << randomZ << '\n';

        glm::vec3 startPosition(randomX, linearFishHeights[i], randomZ);
        glm::vec3 scale(22.f);

        m_fishes.push_back(std::make_shared<Fish>(fishPath, startPosition, scale, linearFishSpeeds[i], movementLimitsX[i], movementLimitsZ[i]));
    }
}

