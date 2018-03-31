//
// Created by opot on 06.04.17.
//

#include <GL/glew.h>
#include <iostream>

#include "MainGame.h"
#include "GlUtils/OrthographicCamera.h"
#include "GlUtils/Shader.h"
#include "GlUtils/SpriteBatch.h"
#include "World.h"
#include "player/Player.h"

namespace fjfj {

    SpriteBatch *batch;
    OrthographicCamera *cam;

    World* world;
    Player* player;

    const int WORLD_WIDTH = 800;
    const int WORLD_HEIGHT = 600;

    Texture *anim;
    Shader *anim_shader;

    void MainGame::init() {

        glEnable(GL_MULTISAMPLE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        batch = new SpriteBatch();
        cam = new OrthographicCamera(WORLD_WIDTH, WORLD_HEIGHT);

        world = new World(batch, cam);
        player = new Player(nullptr, batch, cam);

        anim = new Texture("texture/sprite.png");
        anim_shader = new Shader("shader/animated.vert", "shader/animated.frag");
    }

    float time = 0;
    void MainGame::update(float delta) {
        cam->update();
        player->update(delta);
        time += delta;
    }

    void MainGame::render() {
        glClear(GL_COLOR_BUFFER_BIT);

        //world->render();
        //player->render();

        auto model_loc = glGetUniformLocation(anim_shader->Program, "u_ModelTrans");
        auto proj_loc = glGetUniformLocation(anim_shader->Program, "u_ProjTrans");
        auto frameCount_loc = glGetUniformLocation(anim_shader->Program, "u_FrameCount");
        auto frameTime_loc = glGetUniformLocation(anim_shader->Program, "u_FrameTime");
        auto time_loc = glGetUniformLocation(anim_shader->Program, "u_Time");

        anim_shader->Use();
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
        glUniform1i(frameCount_loc, 5);
        glUniform1f(frameTime_loc, 0.5);
        glUniform1f(time_loc, time);
        batch->draw(*anim, model_loc, 0, 0, 200, 200);
        glUseProgram(0);

    }

}
