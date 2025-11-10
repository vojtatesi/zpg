#include "DrawableObject.h"

DrawableObject::DrawableObject(std::shared_ptr<Model> m, std::shared_ptr<ShaderProgram> s)
	: model(std::move(m)), shader(std::move(s)), transform(std::make_shared<Transformation>()) {
}

void DrawableObject::addChildObject(const std::shared_ptr<DrawableObject>& child) {
	transform->addChild(child->getTransformation());
	children.push_back(child);
}


void DrawableObject::draw() const
{
	model->draw();
}

std::shared_ptr<ShaderProgram> DrawableObject::getShader() const {
	return shader;
}


void DrawableObject::setColor(const glm::vec4& c)
{
	color = c;
}