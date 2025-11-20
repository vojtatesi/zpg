#pragma once
#include <memory>
#include <vector>
#include "DrawableObject.h"
#include "Light.h"
#include "Skybox.h"

class Scene {
public:
    void addObject(std::shared_ptr<DrawableObject> obj);
    void draw(const std::shared_ptr<Camera>& camera) const;
    void drawObjectRecursive(const std::shared_ptr<DrawableObject>& obj, const std::shared_ptr<Camera>& camera) const;

    void addLight(const std::shared_ptr<Light>& l) { lights.push_back(l); }
    const std::vector<std::shared_ptr<Light>>& getLights() const { return lights; }

    void setSkybox(std::shared_ptr<Skybox> sb) { skybox = sb; }

private:
    std::vector<std::shared_ptr<DrawableObject>> objects;    
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Skybox> skybox;
};
