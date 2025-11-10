#pragma once
#include "Model.h"
#include <cstddef>
#include "sphere_points.h"
#include <GL/glew.h>

extern const float sphere[];

class Sphere : public Model
{
protected:
    const void* getVertices() const override { return sphere; }
    GLsizeiptr getVertexSize() const override { return sizeof(sphere); }
    GLsizei getVertexCount() const override { return std::size(sphere) / 6; }

    void setupVertexAttribs() override;

private:
};