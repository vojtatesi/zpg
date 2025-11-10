#include "PhongShader.h"

PhongShader::PhongShader()
{
	ambientColor = glm::vec3(0.1f);
	shininess = 32.0f;
	specularStrength = 0.5f;
}

void PhongShader::applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) {
	setUniformMatrix4fv("uProjection", camera->getProjection());
	setUniformMatrix4fv("uView", camera->getViewMatrix());
	setUniformMatrix4fv("uModel", model->getTransformation()->getWorldMatrix());
	setUniform4f("uObjectColor", model->getColor());

	setUniform3f("uViewPos", camera->getPosition());
	setUniform3f("uAmbientColor", ambientColor);
	setUniform1f("uShininess", shininess);
	setUniform1f("uSpecularStrength", specularStrength);
}