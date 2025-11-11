#include "Application.h"
#include "ObjectFactory.h"

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
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1200, 1200, "ZPG", NULL, NULL);
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
	addObserver(camera);

	float aspect = static_cast<float>(width) / static_cast<float>(height);
	camera->setMode(CameraMode::Third_person, aspect);

	camera->flashlight = ObjectFactory::createFlashLight();
	camera->flashlight->setInnerCutoff(15.0f);
	camera->flashlight->setOuterCutoff(20.0f);
	camera->flashlight->intensity = 1.5f;
	camera->flashlight->color = glm::vec3(1.0f, 1.0f, 0.2f);
	camera->syncFlashlight();

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
}

void Application::initModels()
{
	auto& sm = SceneManager::getInstance();

	sm.addScene(SceneBuilder::createTriangleScene(constantShader));
	sm.addScene(SceneBuilder::createSpheresScene(phongShader));
	sm.addScene(SceneBuilder::createSolarSystemScene(phongShader, constantShader));
	sm.addScene(SceneBuilder::createComplexScene(phongShader, constantShader));
	sm.addScene(SceneBuilder::createShaderTestScene(phongShader, constantShader, lambertShader, blinnShader));
}


void Application::run()
{
	auto& inputManager = InputManager::getInstance();
	auto& sceneManager = SceneManager::getInstance();
	inputController = std::make_unique<InputController>(camera);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float aspect = static_cast<float>(width) / static_cast<float>(height);

		inputManager.update(window);

		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;

		inputController->update(deltaTime);

		for (int key = GLFW_KEY_1; key <= GLFW_KEY_5; ++key) {
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				int sceneIndex = key - GLFW_KEY_1;
				sceneManager.setActiveScene(sceneIndex);
			}
		}

		auto scene = sceneManager.getActiveScene();

		if (scene)
			scene->draw(camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}