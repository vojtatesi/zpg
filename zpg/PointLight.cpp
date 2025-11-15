#include "PointLight.h"

void PointLight::applyToShader(class ShaderProgram* shader, const std::string& base) const
{
    shader->setUniform3f(base + ".position", position);
    shader->setUniform3f(base + ".color", color * intensity);
    shader->setUniform1i(base + ".type", static_cast<int>(type));

    setAttenuationUniforms(shader, base);
}