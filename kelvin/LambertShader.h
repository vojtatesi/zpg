#pragma once
#include "ShaderProgram.h"
#include <memory>
#include "Light.h"

class LambertShader : public ShaderProgram
{
public:
    LambertShader();
    void applyUniforms(const std::shared_ptr<Camera>& camera,
        const std::shared_ptr<DrawableObject>& model) override;

    std::string getFragmentSource() override { return LambertFragmentSource; }
    std::string getVertexSource()   override { return LambertVertexSource; }

    void applyLight(const std::shared_ptr<Light>& light) override;

private:
    static const std::string LambertFragmentSource;
    static const std::string LambertVertexSource;

    glm::mat4  projection;
    glm::vec3  ambientColor;
};
