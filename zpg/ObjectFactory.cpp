#include "ObjectFactory.h"

const std::unordered_map<ObjectFactory::ModelType, std::string> ObjectFactory::modelPaths = {
	{ ModelType::Formula, "../Objects/formula1.obj" },
	{ ModelType::House, "../Objects/house.obj" },
	{ ModelType::Cube, "../Objects/cube.obj" },
	{ ModelType::Fiona, "../Objects/fiona.obj" },
	{ ModelType::Shrek, "../Objects/shrek.obj" },
	{ ModelType::Toilet, "../Objects/toiled.obj" }
};


std::shared_ptr<DrawableObject> ObjectFactory::createTriangle(const std::shared_ptr<ShaderProgram>& shader) {
	auto model = std::make_shared<Triangle>();
	model->init();
	return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createSquare(const std::shared_ptr<ShaderProgram>& shader) {
	auto model = std::make_shared<Square>();
	model->init();
	return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createGround(const std::shared_ptr<ShaderProgram>& shader) {
	auto model = std::make_shared<Ground>();
	model->init();
	return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createSphere(const std::shared_ptr<ShaderProgram>& shader) {
	auto model = std::make_shared<Sphere>();
	model->init();
	return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createTree(const std::shared_ptr<ShaderProgram>& shader) {
	auto model = std::make_shared<Tree>();
	model->init();
	return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createBush(const std::shared_ptr<ShaderProgram>& shader) {
	auto model = std::make_shared<Bush>();
	model->init();
	return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createSuziSmooth(const std::shared_ptr<ShaderProgram>& shader) {
	auto model = std::make_shared<Suzi_smooth>();
	model->init();
	return std::make_shared<DrawableObject>(model, shader);
}


std::shared_ptr<PointLight> ObjectFactory::createPointLight() {
	auto model = std::make_shared<PointLight>();
	return model;
}

std::shared_ptr<FlashLight> ObjectFactory::createFlashLight() {
	auto model = std::make_shared<FlashLight>();
	return model;
}

std::unordered_map<std::string, std::weak_ptr<Model>> ObjectFactory::modelCache;
std::shared_ptr<DrawableObject> ObjectFactory::createOBJ(ModelType type, const std::shared_ptr<ShaderProgram>& shader)
{
	auto it = modelPaths.find(type);
	if (it == modelPaths.end()) {
		throw std::runtime_error("Model path not found for requested type.");
	}

	const std::string& path = it->second;


	if (auto cached = modelCache[path].lock()) {
		return std::make_shared<DrawableObject>(cached, shader);
	}
	
	auto model = std::make_shared<OBJModel>(path);
	model->init();
	
	modelCache[path] = model;
	
	return std::make_shared<DrawableObject>(model, shader);
}