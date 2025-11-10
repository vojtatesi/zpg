#include "ConstantShader.h"

ConstantShader::ConstantShader()
{	
}

void ConstantShader::applyLights(const std::vector<std::shared_ptr<Light>>& lights)
{
}


void ConstantShader::applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) {
	setUniformMatrix4fv("uProjection", camera->getProjection());
	setUniformMatrix4fv("uView", camera->getViewMatrix());
	setUniformMatrix4fv("uModel", model->getTransformation()->getWorldMatrix());
	setUniform4f("uObjectColor", model->getColor());
}