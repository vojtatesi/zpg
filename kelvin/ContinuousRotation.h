#pragma once
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "ITransformation.h"

class ContinuousRotation : public ITransformation {
public:
    ContinuousRotation(glm::vec3 axis, float speed)
        : axis(axis), speed(speed) {
    }

    glm::mat4 getMatrix() const override {
        float time = (float)glfwGetTime();
        return glm::rotate(glm::mat4(1.0f), glm::radians(time * speed), axis);
    }

private:
    glm::vec3 axis;
    float speed;
};
