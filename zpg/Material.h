#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"

class Material {
public:
    glm::vec4 color = glm::vec4(1.0f);
    std::shared_ptr<Texture> diffuse;
    std::shared_ptr<Texture> normal;
    std::shared_ptr<Texture> specular;
    float texScale = 1.0f;

    void bind(const ShaderProgram& shader) const;
};
