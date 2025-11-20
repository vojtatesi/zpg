#pragma once
#include "ShaderProgram.h"
class SkyboxShader : public ShaderProgram
{
public:
	SkyboxShader();

	void applyLights(const std::vector<std::shared_ptr<Light>>& lights) override;
	void applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) override;

	std::string getVertexPath() override { return "SkyboxShader.vert"; }
	std::string getFragmentPath() override { return "SkyboxShader.frag"; }
};

