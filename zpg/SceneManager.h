#pragma once
#include "Scene.h"

class SceneManager
{
public:
    static SceneManager& getInstance();

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    void addScene(const std::shared_ptr<Scene>& scene);
    void setActiveScene(int index);
    std::shared_ptr<Scene> getActiveScene() const;

    ~SceneManager();

private:
    SceneManager();

    std::vector<std::shared_ptr<Scene>> scenes;
    int currentScene = 0;
};

