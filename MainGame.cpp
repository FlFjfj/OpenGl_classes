//
// Created by opot on 06.04.17.
//

#include <GL/glew.h>
#include <iostream>

#include "MainGame.h"
#include "GlUtils/OrthographicCamera.h"
#include "GlUtils/Shader.h"

namespace fjfj {

    OrthographicCamera *cam;
    Shader *shader;

    const int WORLD_WIDTH = 800;
    const int WORLD_HEIGHT = 600;

    void MainGame::init() {

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        cam = new OrthographicCamera(WORLD_WIDTH, WORLD_HEIGHT);
        shader = new Shader("shader/simple.vert", "shader/simple.frag");
    }

    void MainGame::update(float delta) {
        cam->update();
    }

    void MainGame::render() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->Use();



        glUseProgram(0);
    }

}
