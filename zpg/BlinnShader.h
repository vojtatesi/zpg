#pragma once
#include "ShaderProgram.h"
#include <memory>

class BlinnShader : public ShaderProgram
{
public:
    BlinnShader();
    void applyUniforms(const std::shared_ptr<Camera>& camera,
        const std::shared_ptr<DrawableObject>& model) override;

    std::string getFragmentPath() override { return "BlinnShader.frag"; }
    std::string getVertexPath()   override { return "BlinnShader.vert"; }

private:
    glm::mat4  projection;
    glm::vec3  ambientColor;
    float      shininess;
    float      specularStrength;
};
