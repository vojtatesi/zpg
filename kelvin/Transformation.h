#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"
#include "CompositeTransformation.h"

class Transformation : public std::enable_shared_from_this<Transformation>
{
public:
    std::shared_ptr<Transformation> translate(const glm::vec3& offset);
    std::shared_ptr<Transformation> translate(float x, float y, float z);

    std::shared_ptr<Transformation> rotate(const glm::vec3& angleDegrees);
    std::shared_ptr<Transformation> rotate(float x, float y, float z);

    std::shared_ptr<Transformation> scale(const glm::vec3& factor);
    std::shared_ptr<Transformation> scale(float uniformFactor);

    void addChild(const std::shared_ptr<Transformation>& child);
    void addDynamicChild(const std::shared_ptr<ITransformation>& child);

    glm::mat4 getLocalMatrix() const;
    glm::mat4 getWorldMatrix() const;


private:
    std::weak_ptr<Transformation> parent;
    std::vector<std::shared_ptr<Transformation>> children;
    std::vector<std::shared_ptr<ITransformation>> dynamicChildren;
    glm::vec3 position{ 0.0f };
    glm::vec3 rotation{ 0.0f };
    glm::vec3 scaleFactor{ 1.0f };
    glm::vec3 pivot{ 0.0f };
};
