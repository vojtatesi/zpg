#pragma once
#include "ITransformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public ITransformation {
public:
    explicit Scale(const glm::vec3& factor) : factor(factor) {}
    glm::mat4 getMatrix() const override {
        return glm::scale(glm::mat4(1.0f), factor);
    }
private:
    glm::vec3 factor;
};