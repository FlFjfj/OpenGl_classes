//
// Created by opot on 23.04.17.
//

#include "../GlUtils/MeshLoader.h"

#include "Player.h"
#include "../GlUtils/OrthographicCamera.h"

Player::Player(PlayerController *controller, SpriteBatch *batch, OrthographicCamera *cam)
        : controller(controller),
          batch(batch), cam(cam) {
    head = new Texture("texture/sprouthead.jpeg");
    tentacle = new Texture("texture/sprouttentacle.jpg");
    shader = new Shader("shader/player.vert", "shader/player.frag");
    model_loc = glGetUniformLocation(shader->Program, "u_ModelTrans");
    proj_loc = glGetUniformLocation(shader->Program, "u_ProjTrans");
    float PI = glm::acos(0) * 2;
    for (int i = 0; i < NTENTACLES; i++) {
        tentacleOffsets[i] = glm::vec2(100.0 * glm::cos(0.25 * i * PI), 100.0 * glm::sin(0.25 * i * PI));
    }
    coords = glm::vec2(0, 0);
    speed = glm::vec2(10, 0);

}

void Player::update(float delta) {
    coords = coords + speed * delta;
}

void Player::render() {
    shader->Use();

    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    float x, y;
    for (int i = 0; i < NTENTACLES; i++) {
        x = coords.x + tentacleOffsets[i].x;
        y = coords.y + tentacleOffsets[i].y;
        batch->draw(*tentacle, model_loc, x, y, TENTACLE_WIDTH, TENTACLE_HEIGHT);
    }

    batch->draw(*head, model_loc, coords.x, coords.y, HEAD_WIDTH, HEAD_HEIGHT);

    glUseProgram(0);
}