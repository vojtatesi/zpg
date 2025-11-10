#pragma once
#include <glm/glm.hpp>
#include <memory>

class ShaderProgram;
class Light
{
public:
    virtual ~Light() = default;

    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;
   
    virtual void applyToShader(class ShaderProgram* shader) const = 0;
};
