#pragma once
#include "Model.h"
#include <cstddef>

class Square : public Model
{
protected:
    const void* getVertices() const override { return points; }
    GLsizeiptr getVertexSize() const override { return sizeof(points); }
    GLsizei getVertexCount() const override { return 6; }

    void setupVertexAttribs() override;

private:
    float points[36] = {       
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,

         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };
};