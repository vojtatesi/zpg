#pragma once
#include "Model.h"
#include "bushes_points.h"

extern const float bushes[];

class Bush : public Model
{
	const void* getVertices() const override { return bushes; }
	GLsizeiptr getVertexSize() const override { return sizeof(bushes); }
	GLsizei getVertexCount() const override { return std::size(bushes) / 6; }

	void setupVertexAttribs() override;

private:

};

