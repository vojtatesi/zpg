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
    return keyStates.at(key);
}

bool InputManager::isKeyReleased(int key) const {
    return !keyStates.at(key) && prevKeyStates.at(key);
}

bool InputManager::isMouseButtonPressed(int button) const {
    auto it = mouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second;
}
