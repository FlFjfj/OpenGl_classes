#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include "PlayerController.h"


std::queue<Event> PlayerController::qclicks = std::queue<Event>();

PlayerController::PlayerController(GLFWwindow *window) : window(window) {
    glfwSetMouseButtonCallback(window, mouseClickHandler);
}

void PlayerController::mouseClickHandler(GLFWwindow *window, int button, int action, int mods) {
    Event e;
    double pos[2];
    int w, h;
    glfwGetCursorPos(window, pos, pos + 1);
    glfwGetWindowSize(window, &w, &h);
    glm::vec2 mousecoords = glm::vec2(pos[0]/w, pos[1]/h);
    mousecoords = 2.0f*mousecoords - glm::vec2(1,1);
    e.data.delta[0] = mousecoords.x;
    e.data.delta[1] = -mousecoords.y;
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_RELEASE) {
                e.type = M_RELEASE_LEFT;
                qclicks.push(e);
            }

            break;

        case GLFW_MOUSE_BUTTON_RIGHT:
            if (action == GLFW_RELEASE) {
                e.type = M_RELEASE_RIGHT;
                qclicks.push(e);
            }

            break;

        default:
            break;
    }

}

Event PlayerController::getEvent() {
    Event e = qclicks.front();
    qclicks.pop();
    return e;
}

bool PlayerController::hasEvent() {
    return !qclicks.empty();
}


bool PlayerController::moveTop() {
    return glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
}

bool PlayerController::moveRight() {
    return glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
}

bool PlayerController::moveLeft() {
    return glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
}

bool PlayerController::moveBottom() {
    return glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
}