#pragma once
#include "ITransformation.h"
#include <vector>
#include <memory>

class CompositeTransformation : public ITransformation {
public:
    void add(const std::shared_ptr<ITransformation>& t) {
        transforms.push_back(t);
    }

    glm::mat4 getMatrix() const override;

private:
    std::vector<std::shared_ptr<ITransformation>> transforms;
};
