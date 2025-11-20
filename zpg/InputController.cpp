#include "InputController.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

InputController::InputController(std::shared_ptr<Camera> cam)
	: camera(std::move(cam)) {
}

void InputController::update(float deltaTime) {
	auto& input = InputManager::getInstance();
	auto& sceneManager = SceneManager::getInstance();

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

	if (input.isMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT)) {
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		GLint x = static_cast<GLint>(input.getMouseX());
		GLint y = static_cast<GLint>(input.getMouseY());

		int flippedY = camera->getResolution().height - 1 - y;

		glReadPixels(x, flippedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, flippedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, flippedY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u \n", x, y, color[0], color[1], color[2], color[3], depth, index);

		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 proj = camera->getProjection();
		glm::vec4 viewport(0.0f, 0.0f, static_cast<float>(camera->getResolution().width), static_cast<float>(camera->getResolution().height));

		float winX = static_cast<float>(x);
		float winY = static_cast<float>(flippedY);

		glm::vec3 worldNear = glm::unProject(glm::vec3(winX, winY, 0.0f),
			view, proj, viewport);
		glm::vec3 worldFar = glm::unProject(glm::vec3(winX, winY, 1.0f),
			view, proj, viewport);
		glm::vec3 dir = glm::normalize(worldFar - worldNear);

		// 2) Prùseèík s rovinou zemì y = 0
//    worldNear + t * dir, chceme y = 0 => t = -near.y / dir.y
		if (glm::abs(dir.y) > 1e-4f) { // bezpeènost proti dìlení nulou
			float t = -worldNear.y / dir.y;

			if (t > 0.0f) { // pøed kamerou
				glm::vec3 hit = worldNear + t * dir;
				printf("Ground hit at: (%.2f, %.2f, %.2f)\n", hit.x, hit.y, hit.z);

				// auto& sceneManager = SceneManager::getInstance();
				// auto scene = sceneManager.getActiveScene();
				// auto tree = ObjectFactory::createTree(phongShader);
				// tree->getTransformation()->translate(hit.x, 0.0f, hit.z)->scale(0.5f);
				// scene->addObject(tree);
			}
		}
	}

	for (int key = GLFW_KEY_1; key <= GLFW_KEY_6; ++key) {
		if (input.isKeyPressed(key)) {
			int sceneIndex = key - GLFW_KEY_1;
			sceneManager.setActiveScene(sceneIndex);
		}
	}

	if (input.isKeyReleased(GLFW_KEY_7)) {
		camera->setMode(Camera::CameraMode::First_person);
	}
	if (input.isKeyReleased(GLFW_KEY_8)) {
		camera->setMode(Camera::CameraMode::Third_person);
	}
	if (input.isKeyReleased(GLFW_KEY_9)) {
		camera->setMode(Camera::CameraMode::Fish_eye);
	}

	if (input.isKeyReleased(GLFW_KEY_F)) {
		if (camera->flashlight)
			camera->flashlight->toggle();
	}
}