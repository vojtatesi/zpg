#include "Shader.h"
#include <iostream>
#include <vector>

Shader::Shader(GLenum type, const std::string& source)
	: shaderType(type), shaderSource(source)
{
}

Shader::~Shader()
{
	if (shaderID != 0)
		glDeleteShader(shaderID);
}

bool Shader::compile()
{
	shaderID = glCreateShader(shaderType);
	const char* src = shaderSource.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	GLint status = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		GLint logLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<GLchar> log(logLength);
		glGetShaderInfoLog(shaderID, logLength, nullptr, log.data());

		std::cerr << "Shader compile error ("
			<< (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
			<< "): " << log.data() << std::endl;

		glDeleteShader(shaderID);
		shaderID = 0;
		return false;
	}

	return true;
}

const std::string Shader::RainbowVertexSource =
R"(
    #version 330 core
    layout(location = 0) in vec3 vp;
    layout(location = 1) in vec3 vn;

    uniform mat4 uModel;
    uniform mat4 uViewPos;
    uniform mat4 uProjection;

    out vec3 vertexColor;

    void main() {
        vertexColor = vn;
        gl_Position = uProjection * uViewPos * uModel * vec4(vp, 1.0);
    }
)";

const std::string Shader::RainbowFragmentSource =
R"(
    #version 330 core
    in vec3 vertexColor;
    out vec4 frag_colour;

    void main() {
        frag_colour = vec4(vertexColor, 1.0);
    }
)";

const std::string Shader::BasicVertexSource = R"(
#version 330 core

layout(location = 0) in vec3 vp;

uniform mat4 uModel;
uniform mat4 uViewPos;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uViewPos * uModel * vec4(vp, 1.0);
}
)";


const std::string Shader::BasicFragmentSource = R"(
#version 330 core
out vec4 fragColor;
uniform vec4 uColor;

void main() {
    fragColor = uColor;
}
)";