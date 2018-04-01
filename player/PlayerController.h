//
// Created by opot on 23.04.17.
//

#ifndef GLUTGL_PLAYERCONTROLLER_H
#define GLUTGL_PLAYERCONTROLLER_H


#include <GLFW/glfw3.h>
#include <queue>

enum EventType {
    KeyDown, KeyUp, MouseMove, M_RELEASE_LEFT, M_RELEASE_RIGHT
};

enum EventKey {
    UP, DOWN, LEFT, RIGHT, MOUSE
};

typedef union {
    EventKey key;
    float delta[2];
} EventData;

struct Event {
    EventType type;
    EventData data;
};

class PlayerController {

protected:
    static std::queue<Event> qclicks;
    GLFWwindow *window;

public:

    PlayerController(GLFWwindow *window);

    static void mouseClickHandler(GLFWwindow *window, int button, int action, int mods);

    Event getEvent();

    bool hasEvent();

    bool moveTop();

    bool moveRight();

    bool moveLeft();

    bool moveBottom();

    bool unconnectAll();
};


#endif //GLUTGL_PLAYERCONTROLLER_H
