#pragma once
#include <glm/fwd.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera {
public:
    Camera(
        glm::vec3 eye = glm::vec3(0.0f, 5.0f, 15.0f),
        glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
        : eye(eye), target(target), up(up) {
    }

    void setPosition(const glm::vec3& newEye) { eye = newEye; }
    void setTarget(const glm::vec3& newTarget) { target = newTarget; }  
    void setUp(const glm::vec3& newUp) { up = newUp; }

    const glm::vec3& getPosition() const { return eye; }
    const glm::vec3& getTarget() const { return target; }
    const glm::vec3& getUp() const { return up; }
    
    void moveForward(float amount) { eye += glm::normalize(target) * amount; }
    void moveBackward(float amount) { eye -= glm::normalize(target) * amount; }
    void moveLeft(float amount) { eye -= glm::normalize(glm::cross(target, up)) * amount; }
    void moveRight(float amount) { eye += glm::normalize(glm::cross(target, up)) * amount; }

    glm::mat4 getViewMatrix() const;

private:
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;
};