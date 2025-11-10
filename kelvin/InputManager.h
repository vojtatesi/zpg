#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputManager {
public:
    static InputManager& getInstance();

    void update(GLFWwindow* window);

    bool isKeyPressed(int key) const;
    bool isKeyReleased(int key) const;
    bool isMouseButtonPressed(int button) const;

    double getMouseX() const { return mouseX; }
    double getMouseY() const { return mouseY; }
    double getMouseDeltaX() const { return mouseDeltaX; }
    double getMouseDeltaY() const { return mouseDeltaY; }

private:
    InputManager() = default;

    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, bool> prevKeyStates;
    std::unordered_map<int, bool> mouseButtonStates;

    double mouseX = 0.0, mouseY = 0.0;
    double prevMouseX = 0.0, prevMouseY = 0.0;
    double mouseDeltaX = 0.0, mouseDeltaY = 0.0;
};
