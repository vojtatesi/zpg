#include "OBJModel.h"
#include <tiny_obj_loader.h>
#include <iostream>

OBJModel::OBJModel(const std::string& path) {
    loadOBJ(path);
    init();
}

void OBJModel::loadOBJ(const std::string& path) {
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(path)) {
        std::cerr << "Failed to load OBJ: " << path << "\n";
        if (!reader.Error().empty()) std::cerr << reader.Error() << std::endl;
        return;
    }

    const auto& attrib = reader.GetAttrib();
    const auto& shapes = reader.GetShapes();

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex v{};
            v.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };
            if (!attrib.normals.empty())
                v.nor = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
            };
            if (!attrib.texcoords.empty())
                v.tex = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1]
            };
            vertices.push_back(v);
        }
    }
}

void OBJModel::setupVertexAttribs() {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nor));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
}
