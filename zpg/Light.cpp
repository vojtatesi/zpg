#include "Light.h"
#include "ShaderProgram.h"

void Light::setAttenuationUniforms(ShaderProgram* shader, const std::string& base) const {
    shader->setUniform1f(base + ".constant", this->constant);
    shader->setUniform1f(base + ".linear", this->linear);
    shader->setUniform1f(base + ".quadratic", this->quadratic);
}