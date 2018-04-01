//
// Created by opot on 06.04.17.
//

#include <GL/glew.h>
#include <iostream>

#include "MainGame.h"
#include "../GlUtils/OrthographicCamera.h"
#include "../GlUtils/Shader.h"
#include "../GlUtils/SpriteBatch.h"
#include "../World.h"
#include "../player/Player.h"
#include "../GlUtils/BitmapFont.h"
#include "../environment/Lizard.h"

namespace fjfj {

    SpriteBatch *batch;
    OrthographicCamera *cam;

    World *world;
    Player *player;
    BitmapFont *font;

    float elapsed = 0;

    const int WORLD_WIDTH = 1440;
    const int WORLD_HEIGHT = 920;

    GLFWwindow *win;

    void MainGame::init(GLFWwindow *window) {
        glEnable(GL_MULTISAMPLE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        batch = new SpriteBatch();
        cam = new OrthographicCamera(WORLD_WIDTH, WORLD_HEIGHT);

        world = new World(batch, cam);
        glfwSetMouseButtonCallback(window, PlayerController::mouseClickHandler);
        player = new Player(new PlayerController(window), batch, cam, &world->map);
        font = new BitmapFont("0123456789.", new Texture("texture/font.png"));

        win = window;
    }

    void MainGame::update(float delta) {
        elapsed += delta;
        world->update(delta);
        player->update(delta, elapsed);
        cam->update();
    }

    void MainGame::render() {
        glClear(GL_COLOR_BUFFER_BIT);

        world->render(batch, cam, elapsed);
        player->render(elapsed);

        font->draw(batch, cam, std::to_string(elapsed), -WORLD_WIDTH / 2 + 25, WORLD_HEIGHT / 2 - 25, 40, 40);
    }

    void MainGame::restart() {
        elapsed = 0;
        delete (world);
        delete (player);
        delete (font);
        delete (batch);
        delete (cam);

        MainGame::init(win);
    }

}
