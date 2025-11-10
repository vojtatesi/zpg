#include "CompositeTransformation.h"

glm::mat4 CompositeTransformation::getMatrix() const {
    glm::mat4 m(1.0f);
    for (auto& t : transforms)
        m *= t->getMatrix();
    return m;
}