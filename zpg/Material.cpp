#include "Material.h"
#include "ShaderProgram.h"

void Material::bind(const ShaderProgram& shader) const {
    shader.use();

    shader.setUniform4f("uObjectColor", color);

    if (diffuse) {
        shader.setUniform1i("useTexture", 1);
        diffuse->bind(0);
        shader.setUniform1i("uTexture", 0);
        shader.setUniform1f("uTexScale", texScale);
    }
    else
    {
        shader.setUniform1i("useTexture", 0);
    }
}
