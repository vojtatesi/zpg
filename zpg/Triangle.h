#pragma once
#include "Model.h"
#include <cstddef>
#include <glm/glm.hpp>

class Triangle : public Model
{
public:
    glm::vec3 getPivot() const override;
protected:
    const void* getVertices() const override { return points; }
    GLsizeiptr getVertexSize() const override { return sizeof(points); }
    GLsizei getVertexCount() const override { return 3; }

    void setupVertexAttribs() override;

private:
    float points[9] = {
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f
    };
};
