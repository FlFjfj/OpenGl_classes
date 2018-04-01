//
// Created by opot on 01.04.18.
//

#ifndef GLUTGL_PROGRAMBASE_H
#define GLUTGL_PROGRAMBASE_H


#include <GLFW/glfw3.h>

class ProgramBase {
public:
    enum GameState {
        GAME, MENU,DEAD
    };

    static void init(GLFWwindow* window);
    static void update(float delta);
    static void render();
    static void changeState(GameState state);
};


#endif //GLUTGL_PROGRAMBASE_H
