#include "ShaderProgram.h"
#include "Shader.h"
#include <iostream>
#include <vector>

ShaderProgram::ShaderProgram() : programID(0) {}

ShaderProgram::~ShaderProgram()
{
    if (programID != 0)
        glDeleteProgram(programID);
}

bool ShaderProgram::compileAndLink()
{
    auto vertexSource = getVertexSource();
    auto fragmentSource = getFragmentSource();

    Shader vertexShader(GL_VERTEX_SHADER, vertexSource);
    Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (!vertexShader.compile() || !fragmentShader.compile())
        return false;

    return linkShaders(vertexShader.getID(), fragmentShader.getID());
}

bool ShaderProgram::linkShaders(GLuint vertexShaderID, GLuint fragmentShaderID)
{
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    GLint status = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        GLint logLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> log(logLength);
        glGetProgramInfoLog(programID, logLength, nullptr, log.data());

        std::cerr << "Program link error: " << log.data() << std::endl;

        glDeleteProgram(programID);
        programID = 0;
        return false;
    }

    return true;
}

void ShaderProgram::use() const
{
    if (programID != 0)
        glUseProgram(programID);
}

bool ShaderProgram::hasUniform(const std::string& name) const
{
    if (programID == 0) return false;
    GLint loc = glGetUniformLocation(programID, name.c_str());
    return loc != -1;
}

void ShaderProgram::setUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const
{
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc >= 0)
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform1f(const std::string& name, float value) const
{
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc >= 0)
        glUniform1f(loc, value);
}

void ShaderProgram::setUniform3f(const std::string& name, const glm::vec3& value) const
{
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc >= 0)
        glUniform3fv(loc, 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform4f(const std::string& name, const glm::vec4& value) const
{
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc >= 0)
        glUniform4fv(loc, 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform1i(const std::string& name, int value) const
{
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc >= 0)
        glUniform1i(loc, value);
}
