#include "Scene.h"

void Scene::addObject(std::shared_ptr<DrawableObject> obj) {
	objects.push_back(obj);
}

void Scene::drawObjectRecursive(const std::shared_ptr<DrawableObject>& obj, const std::shared_ptr<Camera>& camera) const
{
	auto shader = obj->getShader();
	shader->use();

	std::vector<std::shared_ptr<Light>> activeLights = lights;
	if (camera->flashlight)
		activeLights.push_back(camera->flashlight);

	if (activeLights.size() >= 1)
		shader->applyLights(activeLights);

	shader->applyUniforms(camera, obj);

	obj->draw();

	for (const auto& child : obj->getChildren())
		drawObjectRecursive(child, camera);

	shader->unuse();
}

void Scene::draw(const std::shared_ptr<Camera>& camera) const
{
	for (const auto& obj : objects)
		drawObjectRecursive(obj, camera);
}