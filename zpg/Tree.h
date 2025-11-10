#include <GL/glew.h>
#include "Model.h"
#include "tree_points.h"
#include <cstddef>

extern const float tree[];

class Tree : public Model {
protected:
	const void* getVertices() const override { return tree; }
	GLsizeiptr getVertexSize() const override { return sizeof(tree); }
	GLsizei getVertexCount() const override { return std::size(tree) / 6; }

	void setupVertexAttribs() override;

private:	

};