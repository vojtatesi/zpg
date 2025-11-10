#include "SceneManager.h"

SceneManager& SceneManager::getInstance() {
	static SceneManager instance;
	return instance;
}

SceneManager::SceneManager() = default;

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(const std::shared_ptr<Scene>& scene) {
	scenes.push_back(scene);
}

void SceneManager::setActiveScene(int index) {
	if (index >= 0 && index < (int)scenes.size()) {
		currentScene = index;
	}
}

std::shared_ptr<Scene> SceneManager::getActiveScene() const {
	if (scenes.empty()) return nullptr;
	return scenes[currentScene];
}