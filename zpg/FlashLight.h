#pragma once
#include "Light.h"
#include <memory>

class ShaderProgram;
class FlashLight : public Light
{
public:
		
	void applyToShader(class ShaderProgram* shader, const std::string& base) const override;

	const glm::vec3& getPosition() const { return position; }
	const glm::vec3& getDirection() const { return direction; }
	float getInnerCutoff() const { return innerCutoff; }
	float getOuterCutoff() const { return outerCutoff; }

	void setPosition(const glm::vec3& position) { this->position = position; }
	void setDirection(const glm::vec3& direction) { this->direction = direction; }

	void setInnerCutoff(float innerCutoff) {
		this->innerCutoff = glm::cos(glm::radians(innerCutoff));
	}

	void setOuterCutoff(float outerCutoff) {
		this->outerCutoff = glm::cos(glm::radians(outerCutoff));
	}

	void toggle() { enabled = !enabled; }

private:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 direction = glm::vec3(0.0f);
	float innerCutoff = 0;
	float outerCutoff = 0;
	LightType type = LightType::Flash_Light;
	bool enabled = true;
};
