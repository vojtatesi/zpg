#include "PhongShader.h"

PhongShader::PhongShader()
{
    ambientColor = glm::vec3(0.1f);
    shininess = 32.0f;
    specularStrength = 0.5f;

    projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}

void PhongShader::applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) {
    setUniformMatrix4fv("uProjection", projection);
    setUniformMatrix4fv("uView", camera->getViewMatrix());
    setUniformMatrix4fv("uModel", model->getTransformation()->getWorldMatrix());
    setUniform4f("uObjectColor", model->getColor());

    setUniform3f("uViewPos", camera->getPosition());
    setUniform3f("uAmbientColor", ambientColor);
    setUniform1f("uShininess", shininess);
    setUniform1f("uSpecularStrength", specularStrength);
}

void PhongShader::applyLight(const std::shared_ptr<Light>& light)
{
    if (light)
        light->applyToShader(this);
}



const std::string PhongShader::PhongFragmentSource = R"(
#version 400 core

in vec3 worldPos;
in vec3 worldNor;
out vec4 fragColor;

uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uViewPos;
uniform vec4 uObjectColor;
uniform vec3 uAmbientColor;
uniform float uShininess;
uniform float uSpecularStrength;

void main() {
    vec3 N = normalize(worldNor);
    vec3 L = normalize(uLightPos - worldPos);
    vec3 V = normalize(uViewPos - worldPos);
    vec3 R = reflect(-L, N);

    // Difúzní složka
    float diff = max(dot(N, L), 0.0);

    // Spekulární složka
    float spec = pow(max(dot(V, R), 0.0), uShininess);

    vec3 ambient = uAmbientColor;
    vec3 diffuse = diff * uLightColor * uObjectColor.rgb;
    vec3 specular = uSpecularStrength * spec * uLightColor;

    fragColor = vec4(ambient + diffuse + specular, 1.0);
}
)";


const std::string PhongShader::PhongVertexSource = R"(
#version 400 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 worldPos;
out vec3 worldNor;

void main() {
    vec4 worldPosition = uModel * vec4(vp, 1.0);
    worldPos = worldPosition.xyz;
    worldNor = mat3(transpose(inverse(uModel))) * vn;
    gl_Position = uProjection * uView * worldPosition;
}
)";
