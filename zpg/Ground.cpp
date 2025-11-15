#include "Ground.h"

const float points[6 * 8] = {
	1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
};

const void* Ground::getVertices() const
{
	return points;
}
GLsizeiptr Ground::getVertexSize() const
{
	return sizeof(points);
}

void Ground::setupVertexAttribs() {
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
}
