#include "InputController.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

InputController::InputController(std::shared_ptr<Camera> cam)
	: camera(std::move(cam)) {
}

void InputController::update(float deltaTime) {
	auto& input = InputManager::getInstance();

	float move = moveSpeed * deltaTime;
	if (input.isKeyPressed(GLFW_KEY_W)) camera->moveForward(move);
	if (input.isKeyPressed(GLFW_KEY_S)) camera->moveBackward(move);
	if (input.isKeyPressed(GLFW_KEY_A)) camera->moveLeft(move);
	if (input.isKeyPressed(GLFW_KEY_D)) camera->moveRight(move);

	if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		float dx = static_cast<float>(input.getMouseDeltaX());
		float dy = static_cast<float>(input.getMouseDeltaY());

		if (dx != 0.0f || dy != 0.0f) {
			glm::vec3 dir = camera->getTarget();

			glm::mat4 yaw = glm::rotate(glm::mat4(1.0f), -dx * lookSensitivity * deltaTime, glm::vec3(0, 1, 0));
			dir = glm::vec3(yaw * glm::vec4(dir, 0.0f));

			glm::vec3 right = glm::normalize(glm::cross(dir, camera->getUp()));
			glm::mat4 pitch = glm::rotate(glm::mat4(1.0f), -dy * lookSensitivity * deltaTime, right);

			dir = glm::vec3(pitch * glm::vec4(dir, 0.0f));

			camera->setTarget(glm::normalize(dir));
		}
	}

	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	float aspect = static_cast<float>(width) / static_cast<float>(height);

	if (input.isKeyReleased(GLFW_KEY_7)) {
		camera->setMode(CameraMode::First_person, aspect);		
	}
	if (input.isKeyReleased(GLFW_KEY_8)) {
		camera->setMode(CameraMode::Third_person, aspect);		
	}
	if (input.isKeyReleased(GLFW_KEY_9)) {
		camera->setMode(CameraMode::Fish_eye, aspect);		
	}
}