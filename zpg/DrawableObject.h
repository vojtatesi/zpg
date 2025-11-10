#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

class ShaderProgram;
class DrawableObject {
public:
    DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shader);

    void draw() const;
    void setColor(const glm::vec4& c);
    const glm::vec4& getColor() { return color; }
    std::shared_ptr<ShaderProgram> getShader() const;

    void addChildObject(const std::shared_ptr<DrawableObject>& child);
    std::vector<std::shared_ptr<DrawableObject>> getChildren() { return children; }

    std::shared_ptr<Transformation> getTransformation() { return transform; }

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<ShaderProgram> shader;
    std::shared_ptr<Transformation> transform;
    std::vector<std::shared_ptr<DrawableObject>> children;
    glm::vec4 color{ 1.0f };
};
