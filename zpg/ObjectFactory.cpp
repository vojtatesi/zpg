#include "ObjectFactory.h"

std::shared_ptr<DrawableObject> ObjectFactory::createTriangle(const std::shared_ptr<ShaderProgram>& shader) {
    auto model = std::make_shared<Triangle>();
    model->init();
    return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createSquare(const std::shared_ptr<ShaderProgram>& shader) {
    auto model = std::make_shared<Square>();
    model->init();
    return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createGround(const std::shared_ptr<ShaderProgram>& shader) {
    auto model = std::make_shared<Ground>();
    model->init();
    return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createSphere(const std::shared_ptr<ShaderProgram>& shader) {
    auto model = std::make_shared<Sphere>();
    model->init();
    return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createTree(const std::shared_ptr<ShaderProgram>& shader) {
    auto model = std::make_shared<Tree>();
    model->init();
    return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createBush(const std::shared_ptr<ShaderProgram>& shader) {
    auto model = std::make_shared<Bush>();
    model->init();
    return std::make_shared<DrawableObject>(model, shader);
}

std::shared_ptr<DrawableObject> ObjectFactory::createSuziSmooth(const std::shared_ptr<ShaderProgram>& shader) {
    auto model = std::make_shared<Suzi_smooth>();
    model->init();
    return std::make_shared<DrawableObject>(model, shader);
}


std::shared_ptr<PointLight> ObjectFactory::createPointLight() {
    auto model = std::make_shared<PointLight>();    
    return model;
}

std::shared_ptr<FlashLight> ObjectFactory::createFlashLight() {
    auto model = std::make_shared<FlashLight>();
    return model;
}