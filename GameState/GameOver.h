//
// Created by opot on 01.04.18.
//

#ifndef GLUTGL_GAMEOVER_H
#define GLUTGL_GAMEOVER_H


#include <GLFW/glfw3.h>

namespace fjfj {

    class GameOver {
    public:
        static void init(GLFWwindow *window);

        static void update(float delta);

        static void render();

        static void setScore(float time);
    };

}
#endif //GLUTGL_GAMEOVER_H
