#pragma once
#include "ShaderProgram.h"
#include <memory>
#include "Light.h"

class PhongShader : public ShaderProgram
{
public:
	PhongShader();
	void applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) override;

	std::string getFragmentPath() override { return "PhongShader.frag"; }
	std::string getVertexPath() override { return "PhongShader.vert"; }

private:
	glm::vec3 ambientColor;
	float shininess;
	float specularStrength;
};

