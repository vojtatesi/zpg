#include "LambertShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

LambertShader::LambertShader()
{
    ambientColor = glm::vec3(0.1f);    
}

void LambertShader::applyUniforms(const std::shared_ptr<Camera>& camera,
    const std::shared_ptr<DrawableObject>& model)
{
    setUniformMatrix4fv("uProjection", camera->getProjection());
    setUniformMatrix4fv("uView", camera->getViewMatrix());
    setUniformMatrix4fv("uModel", model->getTransformation()->getWorldMatrix());

    setUniform4f("uObjectColor", model->getColor());
    setUniform3f("uAmbientColor", ambientColor);
}