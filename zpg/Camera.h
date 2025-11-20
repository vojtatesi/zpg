#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IResizeObserver.h"
#include "FlashLight.h"

class Camera : public IResizeObserver {
public:
	std::shared_ptr<FlashLight> flashlight;

	enum class CameraMode {
		Third_person,
		First_person,
		Fish_eye
	};

	struct resolution {
		float height;
		float width;
	};

	Camera(
		glm::vec3 eye = glm::vec3(0.0f, 2.0f, 15.0f),
		glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		CameraMode mode = CameraMode::Third_person,
		float aspect = 1.0		
	)
		: eye(eye), target(target), up(up), projection(1.0f), mode(mode), aspect(aspect)
	{
		res.height = 1;
		res.width = 1;
	}

	void setPosition(const glm::vec3& newEye) {
		eye = newEye;
		syncFlashlight();
	}
	
	void setResolution(float height, float width);
	void setTarget(const glm::vec3& newTarget);
	void setUp(const glm::vec3& newUp) { up = newUp; }
	const glm::vec3& getPosition() const { return eye; }
	const glm::vec3& getTarget() const { return target; }
	const glm::vec3& getUp() const { return up; }
	const glm::mat4& getProjection() const { return projection; }
	const resolution getResolution() const { return res; }

	void moveForward(float amount) {
		setPosition(eye + glm::normalize(target) * amount);
	}

	void moveBackward(float amount) {
		setPosition(eye - glm::normalize(target) * amount);
	}

	void moveLeft(float amount) {
		setPosition(eye - glm::normalize(glm::cross(target, up)) * amount);
	}

	void moveRight(float amount) {
		setPosition(eye + glm::normalize(glm::cross(target, up)) * amount);
	}

	glm::mat4 getViewMatrix() const;

	void onResize(int width, int height) override;

	void setMode(CameraMode newMode);
	void applyMode();
	void syncFlashlight();

private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 projection;
	CameraMode mode;
	float aspect;

	resolution res;
};