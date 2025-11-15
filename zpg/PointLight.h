#pragma once
#include "Light.h"
#include <memory>
#include "ShaderProgram.h"

class ShaderProgram;
class PointLight : public Light
{
public:
    glm::vec3 position = glm::vec3(0.0f);

    void applyToShader(class ShaderProgram* shader, const std::string& base) const override;
private:
    LightType type = LightType::Point_Light;
};
