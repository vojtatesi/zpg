#pragma once
#include <memory>
#include "Camera.h"
#include "InputManager.h"

class InputController {
public:
    InputController(std::shared_ptr<Camera> camera);

    void update(float deltaTime);

private:
    std::shared_ptr<Camera> camera;
    float moveSpeed = 6.0f;
    float lookSensitivity = 0.1f;
};