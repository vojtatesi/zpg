#pragma once
#include "ShaderProgram.h"

class ConstantShader : public ShaderProgram
{
public:
	ConstantShader();
	void applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) override;
	void applyLight(const std::shared_ptr<Light>& light) override;

	std::string getFragmentSource() override { return FragmentSource; }
	std::string getVertexSource() override { return VertexSource; }

private:
	static const std::string FragmentSource;
	static const std::string VertexSource;

	glm::mat4 projection;
};

