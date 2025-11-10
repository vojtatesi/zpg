#pragma once
#include "ITransformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Translation : public ITransformation {
public:
    explicit Translation(const glm::vec3& offset) : offset(offset) {}
    glm::mat4 getMatrix() const override {
        return glm::translate(glm::mat4(1.0f), offset);
    }
private:
    glm::vec3 offset;
};
