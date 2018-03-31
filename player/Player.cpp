
#include <iostream>
#include "../GlUtils/MeshLoader.h"

#include "Player.h"
#include "../GlUtils/OrthographicCamera.h"
#include "PlayerController.h"

Player::Player(PlayerController *controller, SpriteBatch *batch, OrthographicCamera *cam)
        : controller(controller),
          batch(batch), cam(cam) {
    head = new Texture("texture/sprouthead.png");
    tentacle = new Texture("texture/sprouttentacle.png");
    shader = new Shader("shader/player.vert", "shader/player.frag");
    model_loc = glGetUniformLocation(shader->Program, "u_ModelTrans");
    proj_loc = glGetUniformLocation(shader->Program, "u_ProjTrans");
    float PI = glm::acos(0) * 2;
    for (int i = 0; i < NTENTACLES; i++) {
        tentacleAngle[i] = 0.25f * i * PI;
        tentacleOffsets[i] = glm::vec2(glm::cos(tentacleAngle[i]),
                                       glm::sin(tentacleAngle[i]));
    }


    coords = glm::vec2(0, 0);
    vertical_speed = glm::vec2(0, 100);
    horizontal_speed = glm::vec2(100, 0);
}

void Player::update(float delta) {
    auto v_offset = delta * vertical_speed;
    auto h_offset = delta * horizontal_speed;
    if (controller->moveBottom()) {
        coords -= v_offset;
    }

    if (controller->moveTop()) {
        coords += v_offset;
    }

    if (controller->moveRight()) {
        coords += h_offset;
    }

    if (controller->moveLeft()) {
        coords -= h_offset;
    }

    for (int i = 0; i < NTENTACLES; i++) {
        float len = glm::length(tentacleOffsets[i]);
        if( len > 1.001) {
            tentacleOffsets[i] -= delta * tentacleOffsets[i]/len;
            len = glm::length(tentacleOffsets[i]);
            if(len < 0.999) {
                tentacleOffsets[i] /= len;
            }
        }
    }

    while (controller->hasEvent()) {
        auto e = controller->getEvent();
        if (e.type == M_RELEASE_LEFT) {
            glm::vec2 coords;
            coords.x = e.data.delta[0];
            coords.y = e.data.delta[1];
            coords = glm::normalize(coords);
            std::cout << "EVENT: x=" << coords.x << " y=" << coords.y << std::endl;
            int inearest = 0;
            float maxnearest = -123;
            for (int i = 0; i < NTENTACLES; i++) {
                float near = glm::dot(coords, tentacleOffsets[i]);
                if ( near > maxnearest)  {
                    inearest = i;
                    maxnearest = near;
                }
            }

            tentacleOffsets[inearest] += 2;

        }
    }
}

void Player::render() {
    shader->Use();

    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    float x, y;
    float PI = glm::acos(0) * 2;
    float correcter = PI / 3;
    for (int i = 0; i < NTENTACLES; i++) {
        x = coords.x + tentacleOffsets[i].x*TENTACLE_OFFSET;
        y = coords.y + tentacleOffsets[i].y*TENTACLE_OFFSET;
        batch->draw(*tentacle, model_loc, x, y, TENTACLE_WIDTH, TENTACLE_HEIGHT, tentacleAngle[i] - correcter);
    }

    batch->draw(*head, model_loc, coords.x, coords.y, HEAD_WIDTH, HEAD_HEIGHT);

    glUseProgram(0);
}