#include "Camera.h"


glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(eye, eye + target, up);
}
