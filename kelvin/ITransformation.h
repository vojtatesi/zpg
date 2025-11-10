#pragma once
#include <glm/glm.hpp>

class ITransformation
{
public:
    virtual ~ITransformation() = default;
    virtual glm::mat4 getMatrix() const = 0;
};

