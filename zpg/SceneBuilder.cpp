#include "SceneBuilder.h"
#include "ObjectFactory.h"
#include "ContinuousRotation.h"

std::shared_ptr<Scene> SceneBuilder::createSolarSystemScene(const std::shared_ptr<ShaderProgram>& phongShader,
	const std::shared_ptr<ShaderProgram>& constantShader)
{
	auto scene = std::make_shared<Scene>();

	auto sun = ObjectFactory::createSphere(constantShader);
	sun->setColor({ 1.0f, 1.0f, 0.2f, 1.0f });
	sun->getTransformation()->scale(2.2);

	auto earth = ObjectFactory::createSphere(phongShader);
	earth->setColor({ 0.2f, 0.4f, 1.0f, 1.0f });
	earth->getTransformation()->translate(2.5f, 0.f, 0.f)->scale(0.2f)->addDynamicChild(std::make_shared<ContinuousRotation>(glm::vec3(0.0f, 1.0f, 0.0f), 50.0f));
	sun->addChildObject(earth);

	auto moon = ObjectFactory::createSphere(phongShader);
	moon->setColor({ 0.3f, 0.3f, 0.3f, 1.0f });
	moon->getTransformation()->translate(2.5f, 0.0f, 0.0f)->scale(0.3f)->addDynamicChild(std::make_shared<ContinuousRotation>(glm::vec3(0, 1, 0), 100.0f));
	earth->addChildObject(moon);

	scene->addObject(sun);

	auto light = ObjectFactory::createPointLight();
	light->position = glm::vec3(10.0f, 10.0f, 10.0f);
	light->color = glm::vec3(1.0f);
	light->intensity = 2.0f;

	scene->addLight(light);

	return scene;
}

std::shared_ptr<Scene> SceneBuilder::createTriangleScene(const std::shared_ptr<ShaderProgram>& shader) {
	auto scene = std::make_shared<Scene>();

	auto triangle = ObjectFactory::createTriangle(shader);
	triangle->setColor({ 1.0f, 0.f, 0.f, 1.0f });
	triangle->getTransformation()->scale(2)->addDynamicChild(std::make_shared<ContinuousRotation>(glm::vec3(0.0f, 1.0f, 0.0f), 50.0f));

	scene->addObject(triangle);

	return scene;
}

std::shared_ptr<Scene> SceneBuilder::createSpheresScene(const std::shared_ptr<ShaderProgram>& shader)
{
	auto scene = std::make_shared<Scene>();

	auto light = ObjectFactory::createPointLight();
	light->position = glm::vec3(0.0f);
	light->color = glm::vec3(1.0f);
	light->intensity = 2.0f;
	scene->addLight(light);

	std::vector<glm::vec3> positions = {
		{ 3.0f,  0.0f, 0.0f },
		{ -3.0f, 0.0f, 0.0f },
		{ 0.0f, 3.0f, 0.0f },
		{ 0.0f, -3.0f, 0.0f }
	};

	for (int i = 0; i < 4; ++i) {
		auto sphere = ObjectFactory::createSphere(shader);
		sphere->setColor({ 1.f, 0.f, 0.f, 1.f });
		sphere->getTransformation()->translate(positions[i])->scale(1.5f);
		scene->addObject(sphere);
	}

	return scene;
}

std::shared_ptr<Scene> SceneBuilder::createComplexScene(const std::shared_ptr<ShaderProgram>& phongShader, const std::shared_ptr<ShaderProgram>& constantShader)
{
	auto scene = std::make_shared<Scene>();

	auto light = ObjectFactory::createPointLight();
	light->position = glm::vec3(20.f, 40.f, 15.f);
	light->color = glm::vec3(0.5f);
	light->intensity = 1.0f;
	scene->addLight(light);

	glm::vec4 skyColor = { 0.5f, 0.7f, 1.0f, 1.0f };
	float wallHeight = 20.0f;
	float wallDistance = 50.0f;

	auto frontWall = ObjectFactory::createSquare(constantShader);
	frontWall->setColor(skyColor);
	frontWall->getTransformation()->scale(100.0f)->translate(0.0f, wallDistance, wallDistance);
	scene->addObject(frontWall);

	auto backWall = ObjectFactory::createSquare(constantShader);
	backWall->setColor(skyColor);
	backWall->getTransformation()->scale(100.0f)->rotate(0.0f, 180.0f, 0.0f)->translate(0.0f, wallDistance, -wallDistance);
	scene->addObject(backWall);

	auto leftWall = ObjectFactory::createSquare(constantShader);
	leftWall->setColor(skyColor);
	leftWall->getTransformation()->scale(100.0f)->rotate(0.0f, 90.0f, 0.0f)->translate(-wallDistance, wallDistance, 0.0f);
	scene->addObject(leftWall);

	auto rightWall = ObjectFactory::createSquare(constantShader);
	rightWall->setColor(skyColor);
	rightWall->getTransformation()->scale(100.0f)->rotate(0.0f, -90.0f, 0.0f)->translate(wallDistance, wallDistance, 0.0f);
	scene->addObject(rightWall);

	auto sky = ObjectFactory::createGround(constantShader);
	sky->setColor(skyColor);
	sky->getTransformation()->scale(100.0f)->translate(0.0f, wallDistance, 0.f);
	scene->addObject(sky);

	auto ground = ObjectFactory::createGround(phongShader);
	ground->setColor({ 0.3f, 0.7f, 0.3f, 1.0f });
	ground->getTransformation()->scale(100.0f);
	scene->addObject(ground);

	/*for (int i = 0; i < 50; ++i) {
		auto sphere = ObjectFactory::createSphere(phongShader);

		float x = (rand() % 100 - 50);
		float z = (rand() % 100 - 50);

		sphere->getTransformation()->translate(x, 0.5f, z)->scale(0.3f);

		scene->addObject(sphere);
	}*/

	for (int i = 0; i < 150; ++i) {
		auto tree = ObjectFactory::createTree(phongShader);

		float x = (rand() % 100 - 50);
		float z = (rand() % 100 - 50);

		tree->setColor({ 0.3f, 0.8f, 0.3f, 1.0f });
		tree->getTransformation()->translate(x, 0.f, z)->scale(0.5f);

		scene->addObject(tree);
	}

	for (int i = 0; i < 250; ++i) {
		auto bush = ObjectFactory::createBush(phongShader);

		float x = (rand() % 100 - 50);
		float z = (rand() % 100 - 50);

		bush->setColor({ 0.3f, 0.8f, 0.3f, 1.0f });
		bush->getTransformation()->translate(x, 0.f, z)->scale(2.f);

		scene->addObject(bush);
	}

	return scene;
}

std::shared_ptr<Scene> SceneBuilder::createShaderTestScene(const std::shared_ptr<ShaderProgram>& phongShader, const std::shared_ptr<ShaderProgram>& constantShader,
	const std::shared_ptr<ShaderProgram>& lambertShader, const std::shared_ptr<ShaderProgram>& blinnShader)
{
	auto scene = std::make_shared<Scene>();
	auto red = glm::vec4(1, 0, 0, 1);

	auto light = ObjectFactory::createPointLight();
	light->position = glm::vec3(-3.f, 0.f, 5.f);
	light->color = glm::vec3(1.f);
	light->intensity = 2.f;
	light->linear = 0.09;
	light->quadratic = 0.032;

	scene->addLight(light);

	auto light2 = ObjectFactory::createPointLight();
	light2->position = glm::vec3(12.f, 0.f, 5.f);
	light2->color = glm::vec3(1.f);
	light2->intensity = 2.f;
	light2->linear = 0.09;
	light2->quadratic = 0.032;

	scene->addLight(light2);

	auto light3 = ObjectFactory::createPointLight();
	light3->position = glm::vec3(-3.f, 0.f, -5.f);
	light3->color = glm::vec3(1.f);
	light3->intensity = 2.f;
	light3->linear = 0.09;
	light3->quadratic = 0.032;

	scene->addLight(light3);

	auto suziConstant = ObjectFactory::createSuziSmooth(constantShader);
	suziConstant->setColor(red);
	suziConstant->getTransformation()->scale(1.5)->translate(-6, 0, -1);

	auto suziPhong = ObjectFactory::createSuziSmooth(phongShader);
	suziPhong->setColor(red);
	suziPhong->getTransformation()->translate(3, 0, 0);
	suziConstant->addChildObject(suziPhong);

	auto suziLambert = ObjectFactory::createSuziSmooth(lambertShader);
	suziLambert->setColor(red);
	suziLambert->getTransformation()->translate(3, 0, 0);
	suziPhong->addChildObject(suziLambert);

	auto suziBlinn = ObjectFactory::createSuziSmooth(blinnShader);
	suziBlinn->setColor(red);
	suziBlinn->getTransformation()->translate(3, 0, 0);
	suziLambert->addChildObject(suziBlinn);

	scene->addObject(suziConstant);

	return scene;
}