//
// Created by opot on 01.04.18.
//

#ifndef GLUTGL_MAINMENU_H
#define GLUTGL_MAINMENU_H


#include <GLFW/glfw3.h>

class MainMenu {
public:
    static void init(GLFWwindow *window);

    static void update(float delta);

    static void render();
};


#endif //GLUTGL_MAINMENU_H
