#pragma once
#include "Light.h"
#include <memory>
#include "ShaderProgram.h"

class ShaderProgram;
class PointLight : public Light
{
public:
    glm::vec3 position = glm::vec3(0.0f);

    void applyToShader(class ShaderProgram* shader, const std::string& base) const override
    {
        shader->setUniform3f(base + ".position", position);
        shader->setUniform3f(base + ".color", color * intensity);
        shader->setUniform1i(base + ".type", static_cast<int>(type));

        setAttenuationUniforms(shader, base);
    }
private:
    LightType type = LightType::Point_Light;
};
