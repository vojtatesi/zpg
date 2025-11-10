#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Model
{
public:
    virtual ~Model() { destroy(); }

    void init();    
    void destroy();
    void draw() const;

    virtual glm::vec3 getPivot() const { return glm::vec3(0.0f); }

protected:
    GLuint VAO = 0;
    GLuint VBO = 0;

    virtual const void* getVertices() const = 0;
    virtual GLsizeiptr getVertexSize() const = 0;
    virtual GLsizei getVertexCount() const = 0;
    virtual void setupVertexAttribs() = 0;    
};
