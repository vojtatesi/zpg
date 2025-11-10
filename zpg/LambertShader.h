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

    std::string getFragmentPath() override { return "LambertShader.frag"; }
    std::string getVertexPath()   override { return "LambertShader.vert"; }
private:
    glm::vec3  ambientColor;
};
