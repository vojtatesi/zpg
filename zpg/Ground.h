#pragma once
#include "Model.h"

class Ground : public Model
{
protected:
    const void* getVertices() const override;
    GLsizeiptr getVertexSize() const override;
    GLsizei getVertexCount() const override { return 6; }

    void setupVertexAttribs() override;

private:    
};