#pragma once
#include "ShaderProgram.h"
#include <memory>
#include "Light.h"

class BlinnShader : public ShaderProgram
{
public:
    BlinnShader();
    void applyUniforms(const std::shared_ptr<Camera>& camera,
        const std::shared_ptr<DrawableObject>& model) override;

    std::string getFragmentSource() override { return BlinnFragmentSource; }
    std::string getVertexSource()   override { return BlinnVertexSource; }

    void applyLight(const std::shared_ptr<Light>& light) override;

private:
    static const std::string BlinnFragmentSource;
    static const std::string BlinnVertexSource;

    glm::mat4  projection;
    glm::vec3  ambientColor;
    float      shininess;
    float      specularStrength;
};
