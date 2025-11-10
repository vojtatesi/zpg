#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(GLenum type, const std::string& source);
    ~Shader();

    bool compile();
    GLuint getID() const { return shaderID; }
   
    static const std::string RainbowVertexSource;
    static const std::string RainbowFragmentSource;

    static const std::string BasicVertexSource;
    static const std::string BasicFragmentSource;

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

protected:
    static const std::string vertexSource;
    static const std::string fragmentSource;

private:
    GLuint shaderID;
    GLenum shaderType;
    std::string shaderSource;
};
