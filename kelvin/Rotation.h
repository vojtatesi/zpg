#pragma once
#include "ITransformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public ITransformation {
public:
    Rotation(const glm::vec3& angleDegree)
        : angle(angleDegree) {
    }

    glm::mat4 getMatrix() const override {
        glm::mat4 m(1.0f);
        m = glm::rotate(m, glm::radians(angle.x), glm::vec3(1, 0, 0));
        m = glm::rotate(m, glm::radians(angle.y), glm::vec3(0, 1, 0));
        m = glm::rotate(m, glm::radians(angle.z), glm::vec3(0, 0, 1));
        return m;
    }
private:
    glm::vec3 angle;
};
