#pragma once
#include "ShaderProgram.h"

class ConstantShader : public ShaderProgram
{
public:
	ConstantShader();
	void applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) override;
	void applyLights(const std::vector<std::shared_ptr<Light>>& lights) override;

	std::string getFragmentPath() override { return "ConstantShader.frag"; }
	std::string getVertexPath() override { return "ConstantShader.vert"; }

};

