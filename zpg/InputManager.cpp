#include "InputManager.h"

InputManager& InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::update(GLFWwindow* window) {
    prevKeyStates = keyStates;
    
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
        keyStates[key] = glfwGetKey(window, key) == GLFW_PRESS;
    
    for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button)
        mouseButtonStates[button] = glfwGetMouseButton(window, button) == GLFW_PRESS;
    
    prevMouseX = mouseX;
    prevMouseY = mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    mouseDeltaX = mouseX - prevMouseX;
    mouseDeltaY = mouseY - prevMouseY;
}

bool InputManager::isKeyPressed(int key) const {
    auto it = keyStates.find(key);
    if (it != keyStates.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::isKeyReleased(int key) const {
    bool current = false;
    bool previous = false;

    auto itCurrent = keyStates.find(key);
    if (itCurrent != keyStates.end())
        current = itCurrent->second;

    auto itPrev = prevKeyStates.find(key);
    if (itPrev != prevKeyStates.end())
        previous = itPrev->second;

    return !current && previous;
}

bool InputManager::isMouseButtonPressed(int button) const {
    auto it = mouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second;
}
