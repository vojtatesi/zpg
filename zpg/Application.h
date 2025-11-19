#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "ShaderProgram.h"
#include <iostream>
#include "Shader.h"
#include "PhongShader.h"
#include "ConstantShader.h"
#include "LambertShader.h"
#include "BlinnShader.h"
#include "SceneManager.h"
#include "SceneBuilder.h"
#include "InputManager.h"
#include "InputController.h"
#include "IResizeSubject.h"
#include "SkyboxShader.h"

class Application : IResizeSubject
{
public:
    static Application& getInstance();
    
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    bool init();
    void run();
    void initShaders();
    void initScenes();

    std::shared_ptr<Camera> camera;

    ~Application();

private:
    Application();

    GLFWwindow* window = nullptr;
    std::shared_ptr<ShaderProgram> triangleShader;
    std::shared_ptr<ShaderProgram> constantShader;
    std::shared_ptr<ShaderProgram> phongShader;
    std::shared_ptr<ShaderProgram> lambertShader;
    std::shared_ptr<ShaderProgram> blinnShader;
    std::shared_ptr<ShaderProgram> skyboxShader;

    std::vector<std::shared_ptr<DrawableObject>> models;
    std::vector<std::shared_ptr<Scene>> scenes;
    std::unique_ptr<InputController> inputController;    
};
