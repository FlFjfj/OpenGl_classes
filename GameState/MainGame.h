//
// Created by opot on 06.04.17.
//

#ifndef GLUTGL_MAINGAME_H
#define GLUTGL_MAINGAME_H

#include <GLFW/glfw3.h>

namespace fjfj {

    class MainGame {
    public:
        static void init(GLFWwindow *window);

        static void update(float delta);

        static void render();

        static void restart();
    };

}

#endif //GLUTGL_MAINGAME_H
