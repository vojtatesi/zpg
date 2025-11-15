#include "Camera.h"

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(eye, eye + target, up);
}

void Camera::setTarget(const glm::vec3& newTarget)
{
	target = newTarget;
	syncFlashlight();
}

void Camera::applyMode() {
	switch (mode) {
	case CameraMode::Third_person:
		projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
		break;
	case CameraMode::First_person:
		projection = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);
		break;
	case CameraMode::Fish_eye:
		projection = glm::perspective(glm::radians(130.0f), aspect, 0.1f, 100.0f);
		break;
	}
}

void Camera::syncFlashlight() {
	if (flashlight) {
		flashlight->setPosition(eye);
		flashlight->setDirection(glm::normalize(target));
	}
}

void Camera::setMode(CameraMode newMode) {
	mode = newMode; 
	applyMode();
}

void Camera::onResize(int width, int height) {
	if (height <= 0) return;
	aspect = static_cast<float>(width) / static_cast<float>(height);
	applyMode();
}