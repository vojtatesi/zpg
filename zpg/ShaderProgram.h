#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "DrawableObject.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Light.h"

class Light;
class DrawableObject;
class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    
    bool compileAndLink();
    
    void use() const;
    void unuse() const; 

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    
    bool hasUniform(const std::string& name) const;

    void setUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const;
    void setUniform1f(const std::string& name, float value) const;
    void setUniform3f(const std::string& name, const glm::vec3& value) const;
    void setUniform4f(const std::string& name, const glm::vec4& value) const;
    void setUniform1i(const std::string& name, int value) const;

    virtual void applyLights(const std::vector<std::shared_ptr<Light>>& lights);
    virtual void applyUniforms(const std::shared_ptr<Camera>& camera, const std::shared_ptr<DrawableObject>& model) = 0;
    virtual std::string getVertexPath() = 0;
    virtual std::string getFragmentPath() = 0;

    std::string loadShaderSourceFromFile(std::string filePath);

private:
    GLuint programID;

    bool linkShaders(GLuint vertexShaderID, GLuint fragmentShaderID);
};