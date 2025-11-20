#pragma once
#include <memory>
#include <GL/glew.h>
#include "SkyboxShader.h"
#include "CubeTexture.h"
#include "Camera.h"

class Skybox {
public:
	Skybox(std::shared_ptr<ShaderProgram> shader, std::shared_ptr<CubeTexture> cubemap);

	void draw(const std::shared_ptr<Camera>& camera);

private:
	GLuint VAO = 0;
	GLuint VBO = 0;

	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<CubeTexture> cubemap;

	static float vertices[108];
};
