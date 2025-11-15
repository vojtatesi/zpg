#pragma once
#include "Model.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

class OBJModel : public Model {
public:
    explicit OBJModel(const std::string& path);
    ~OBJModel() override = default;

protected:
    const void* getVertices() const override { return vertices.data(); }
    GLsizeiptr getVertexSize() const override { return vertices.size() * sizeof(Vertex); }
    GLsizei getVertexCount() const override { return static_cast<GLsizei>(vertices.size()); }

    void setupVertexAttribs() override;

private:
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 nor;
        glm::vec2 tex;
    };
    std::vector<Vertex> vertices;

    void loadOBJ(const std::string& path);
};
