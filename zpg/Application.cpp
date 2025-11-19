#include "Application.h"
#include "ObjectFactory.h"
#include <filesystem>
#include <iostream>

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

Application& Application::getInstance() {
	static Application instance;
	return instance;
}

Application::Application() = default;

Application::~Application()
{
	if (window) {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

bool Application::init()
{
	//std::cout << "Current working directory: "
	//	<< std::filesystem::current_path() << std::endl;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1200, 800, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to init GLEW" << std::endl;
		return false;
	}

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window,
		[](GLFWwindow* win, int w, int h) {
			glViewport(0, 0, w, h);

			auto* app = static_cast<Application*>(glfwGetWindowUserPointer(win));
			if (app) {
				app->notifyResize(w, h);
			}
		});

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);	

	camera = std::make_shared<Camera>();
	camera->setResolution(width, height);	
	camera->setMode(Camera::CameraMode::Third_person);

	camera->flashlight = ObjectFactory::createFlashLight();
	camera->flashlight->setInnerCutoff(15.0f);
	camera->flashlight->setOuterCutoff(20.0f);
	camera->flashlight->intensity = 1.5f;
	camera->flashlight->color = glm::vec3(1.0f, 1.0f, 0.2f);
	camera->syncFlashlight();

	addObserver(camera);

	return true;
}


void Application::initShaders()
{
	constantShader = std::make_shared<ConstantShader>();
	constantShader->compileAndLink();

	phongShader = std::make_shared<PhongShader>();
	phongShader->compileAndLink();

	lambertShader = std::make_shared<LambertShader>();
	lambertShader->compileAndLink();

	blinnShader = std::make_shared<BlinnShader>();
	blinnShader->compileAndLink();

	skyboxShader = std::make_shared<SkyboxShader>();
	skyboxShader->compileAndLink();
}

void Application::initScenes()
{
	auto& sm = SceneManager::getInstance();

	sm.addScene(SceneBuilder::createTriangleScene(constantShader));
	sm.addScene(SceneBuilder::createSpheresScene(phongShader));
	sm.addScene(SceneBuilder::createSolarSystemScene(phongShader, constantShader));
	sm.addScene(SceneBuilder::createComplexScene(phongShader, constantShader, skyboxShader));
	sm.addScene(SceneBuilder::createShaderTestScene(phongShader, constantShader, lambertShader, blinnShader));
	sm.addScene(SceneBuilder::createFormulaScene(phongShader));
}


void Application::run()
{
	auto& inputManager = InputManager::getInstance();
	auto& sceneManager = SceneManager::getInstance();
	inputController = std::make_unique<InputController>(camera);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		auto scene = sceneManager.getActiveScene();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		inputManager.update(window);

		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;

		inputController->update(deltaTime);		

		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		if (scene)
			scene->draw(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}