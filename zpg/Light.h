#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>

class ShaderProgram;
class Light
{
public:
    virtual ~Light() = default;

    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;

    float constant = 1;
    float linear = 0;
    float quadratic = 0;
   
    virtual void applyToShader(class ShaderProgram* shader, const std::string& base) const = 0;
protected:
    void setAttenuationUniforms(ShaderProgram* shader, const std::string& base) const;
};
