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
    }

    void MainGame::update(float delta) {
        cam->update();
        player->update(delta);
    }

    void MainGame::render() {
        glClear(GL_DEPTH_BUFFER_BIT);

        world->render();
        player->render();
    }

}
