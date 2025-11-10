#pragma once
#include "ShaderProgram.h"
#include <memory>
#include "Light.h"

class PhongShader : public ShaderProgram
{
public:
	PhongShader();
	void applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) override;

	std::string getFragmentSource() override { return PhongFragmentSource; }
	std::string getVertexSource() override { return PhongVertexSource; }

	void applyLight(const std::shared_ptr<Light>& light) override;

private:
	static const std::string PhongFragmentSource;
	static const std::string PhongVertexSource;

	glm::mat4 projection;
	glm::vec3 ambientColor;
	float shininess;
	float specularStrength;
};

