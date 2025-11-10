#include "Triangle.h"

void Triangle::setupVertexAttribs() {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

glm::vec3 Triangle::getPivot() const {
    glm::vec3 v0(points[0], points[1], points[2]);
    glm::vec3 v1(points[3], points[4], points[5]);
    glm::vec3 v2(points[6], points[7], points[8]);
    return (v0 + v1 + v2) / 3.0f;
}