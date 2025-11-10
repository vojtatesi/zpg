#include "Transformation.h"

void Transformation::addChild(const std::shared_ptr<Transformation>& child) {
    child->parent = shared_from_this();
    children.push_back(child);
}

void Transformation::addDynamicChild(const std::shared_ptr<ITransformation>& dynamicChild) {
    dynamicChildren.push_back(dynamicChild);
}

glm::mat4 Transformation::getLocalMatrix() const {
    CompositeTransformation comp;
    
    for (auto& dyn : dynamicChildren)
        comp.add(dyn);

    comp.add(std::make_shared<Translation>(position));
    comp.add(std::make_shared<Translation>(pivot));
    comp.add(std::make_shared<Rotation>(rotation));
    comp.add(std::make_shared<Scale>(scaleFactor));
    comp.add(std::make_shared<Translation>(-pivot));   

    return comp.getMatrix();
}

glm::mat4 Transformation::getWorldMatrix() const {
    if (auto p = parent.lock())
        return p->getWorldMatrix() * getLocalMatrix();
    return getLocalMatrix();
}

std::shared_ptr<Transformation> Transformation::translate(const glm::vec3& offset) {
    position += offset;
    return shared_from_this();
}

std::shared_ptr<Transformation> Transformation::rotate(const glm::vec3& angleDegrees) {
    rotation += angleDegrees;
    return shared_from_this();
}

std::shared_ptr<Transformation> Transformation::scale(const glm::vec3& factor) {
    scaleFactor *= factor;
    return shared_from_this();
}

std::shared_ptr<Transformation> Transformation::translate(float x, float y, float z) {
    return translate(glm::vec3(x, y, z));
}

std::shared_ptr<Transformation> Transformation::rotate(float x, float y, float z) {
    return rotate(glm::vec3(x, y, z));
}

std::shared_ptr<Transformation> Transformation::scale(float uniformFactor) {
    return scale(glm::vec3(uniformFactor));
}