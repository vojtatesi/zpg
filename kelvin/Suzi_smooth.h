#pragma once
#include "Model.h"
#include <cstddef>
#include "suzi_smooth_points.h"
#include <GL/glew.h>

extern const float suziSmooth[];

class Suzi_smooth : public Model
{
	const void* getVertices() const override { return suziSmooth; }
	GLsizeiptr getVertexSize() const override { return sizeof(suziSmooth); }
	GLsizei getVertexCount() const override { return std::size(suziSmooth) / 6; }

	void setupVertexAttribs() override;

};