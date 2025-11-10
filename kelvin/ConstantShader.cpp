#include "ConstantShader.h"

ConstantShader::ConstantShader()
{
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}

void ConstantShader::applyLight(const std::shared_ptr<Light>&)
{
}


void ConstantShader::applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) {
	setUniformMatrix4fv("uProjection", projection);
	setUniformMatrix4fv("uView", camera->getViewMatrix());
	setUniformMatrix4fv("uModel", model->getTransformation()->getWorldMatrix());
	setUniform4f("uObjectColor", model->getColor());
}

const std::string ConstantShader::VertexSource = R"(
#version 330 core

layout(location = 0) in vec3 vp;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(vp, 1.0);
}
)";

const std::string ConstantShader::FragmentSource = R"(
#version 330 core
out vec4 fragColor;
uniform vec4 uObjectColor;

void main() {
    fragColor = uObjectColor;
}
)";