#pragma once
#include "Light.h"
#include <memory>
#include "ShaderProgram.h"

class PointLight : public Light
{
public:
    glm::vec3 position = glm::vec3(0.0f);

    void applyToShader(ShaderProgram* shader) const override
    {
        shader->setUniform3f("uLightPos", position);
        shader->setUniform3f("uLightColor", color * intensity);
    }

};
