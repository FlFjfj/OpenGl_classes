//
// Created by opot on 06.04.17.
//

#include <GL/glew.h>
#include <iostream>

#include "MainGame.h"
#include "GlUtils/OrthographicCamera.h"
#include "GlUtils/Shader.h"
#include "GlUtils/SpriteBatch.h"

namespace fjfj {

    SpriteBatch *batch;
    OrthographicCamera *cam;
    Shader *shader;
    Texture *tex;

    GLint model_loc;
    GLint proj_loc;

    const int WORLD_WIDTH = 800;
    const int WORLD_HEIGHT = 600;

    void MainGame::init() {

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        batch = new SpriteBatch();
        cam = new OrthographicCamera(WORLD_WIDTH, WORLD_HEIGHT);
        tex = new Texture("texture/octo.jpeg");

        shader = new Shader("shader/simple.vert", "shader/simple.frag");
        model_loc = glGetUniformLocation(shader->Program, "u_ModelTrans");
        proj_loc = glGetUniformLocation(shader->Program, "u_ProjTrans");
    }

    void MainGame::update(float delta) {
        cam->update();
    }

    void MainGame::render() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->Use();

        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
        batch->draw(*tex, model_loc, 4, 0, 100, 100);

        glUseProgram(0);
    }

}
