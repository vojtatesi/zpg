#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IResizeObserver.h"

enum class CameraMode {
	Third_person,
	First_person,
	Fish_eye
};

class Camera : public IResizeObserver {
public:
	Camera(
		glm::vec3 eye = glm::vec3(0.0f, 2.0f, 15.0f),
		glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		CameraMode mode = CameraMode::Third_person
	)
		: eye(eye), target(target), up(up), projection(1.0f), mode(mode)
	{				
	}

	void setPosition(const glm::vec3& newEye) { eye = newEye; }
	void setTarget(const glm::vec3& newTarget) { target = newTarget; }
	void setUp(const glm::vec3& newUp) { up = newUp; }

	const glm::vec3& getPosition() const { return eye; }
	const glm::vec3& getTarget() const { return target; }
	const glm::vec3& getUp() const { return up; }
	const glm::mat4& getProjection() const { return projection; }

	void moveForward(float amount) { eye += glm::normalize(target) * amount; }
	void moveBackward(float amount) { eye -= glm::normalize(target) * amount; }
	void moveLeft(float amount) { eye -= glm::normalize(glm::cross(target, up)) * amount; }
	void moveRight(float amount) { eye += glm::normalize(glm::cross(target, up)) * amount; }

	glm::mat4 getViewMatrix() const;

	void onResize(int width, int height) override {
		if (height <= 0) return;
		float aspect = static_cast<float>(width) / static_cast<float>(height);
		setMode(mode, aspect);
	}

	void setMode(CameraMode newMode, float aspectRatio = 1.0f) {
		mode = newMode;

		switch (mode) {
		case CameraMode::Third_person:
			projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
			break;
		case CameraMode::First_person:
			projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
			break;
		case CameraMode::Fish_eye:			
			projection = glm::perspective(glm::radians(130.0f), aspectRatio, 0.1f, 100.0f);
			break;
		}
	}

private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 projection;
	CameraMode mode;
};