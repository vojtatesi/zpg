#include "SkyboxShader.h"

SkyboxShader::SkyboxShader()
{
}

void SkyboxShader::applyLights(const std::vector<std::shared_ptr<Light>>& lights)
{
}


void SkyboxShader::applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) {
    setUniformMatrix4fv("uProjection", camera->getProjection());
    setUniformMatrix4fv("uView", camera->getViewMatrix());
}
