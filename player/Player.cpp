
#include <iostream>
#include "../GlUtils/MeshLoader.h"

#include "Player.h"
#include "../GlUtils/OrthographicCamera.h"
#include "PlayerController.h"
#include "../World.h"

Player::Player(PlayerController *controller, SpriteBatch *batch, OrthographicCamera *cam)
        : controller(controller),
          batch(batch), cam(cam) {
    head = new Texture("texture/head.png");
    tentacle_tex = new Texture("texture/tenta1.png");
    light_shader = new Shader("shader/light.vert", "shader/light.frag");
    tentacle_shader = new Shader("shader/tenta.vert", "shader/tenta.frag");
    model_loc = glGetUniformLocation(light_shader->Program, "u_ModelTrans");
    proj_loc = glGetUniformLocation(light_shader->Program, "u_ProjTrans");

    u_ModelTrans = glGetUniformLocation(tentacle_shader->Program, "u_ModelTrans");
    u_ProjTrans = glGetUniformLocation(tentacle_shader->Program, "u_ProjTrans");
    u_FrameCount = glGetUniformLocation(tentacle_shader->Program, "u_FrameCount");
    u_FrameTime = glGetUniformLocation(tentacle_shader->Program, "u_FrameTime");
    u_Time = glGetUniformLocation(tentacle_shader->Program, "u_Time");

    float PI = glm::acos(0) * 2;
    for (int i = 0; i < NTENTACLES; i++) {
        auto &tentacle = tentacles[i];
        tentacle.angle = 0.25f * i * PI;
        tentacle.begin_coords = {0, 0};
        tentacle.end_coords = {0, 0};
        tentacle.speed = 0;
        tentacle.state = SLEEEP;

    }

    coords = {0, 0};
    vertical_speed = {0, 300};
    horizontal_speed = {300, 0};
}

void Player::update(float delta) {
   // elapsed += delta;
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

    auto r = coords - cam->position;
    float maxsize = World::PART_SIZE * World::WORLD_SIZE;
    if (glm::length(r) > CAMRAD) {
        auto newpos = cam->position + glm::normalize(r) * (glm::length(r) - float(CAMRAD));
        if (World::WORLD_WIDTH / 2 - maxsize / 2 < newpos.x && newpos.x < maxsize / 2 - World::WORLD_WIDTH / 2) {
            cam->position.x = newpos.x;
        }

        if (World::WORLD_HEIGHT / 2 - maxsize / 2 < newpos.y && newpos.y < maxsize / 2 - World::WORLD_HEIGHT / 2) {
            cam->position.y = newpos.y;
        }
    }

    if (coords.x < -maxsize / 2) {
        coords.x = -maxsize / 2;
    }

    if (coords.x > maxsize / 2) {
        coords.x = maxsize / 2;
    }

    if (coords.y < -maxsize / 2) {
        coords.y = -maxsize / 2;
    }

    if (coords.y > maxsize / 2) {
        coords.y = maxsize / 2;
    }
    while (controller->hasEvent()) {
        auto e = controller->getEvent();
        auto target = translateToGameCoords(e.data.delta[0], e.data.delta[1]);
        int bestIndex = -1;
        float bestLen = 1000000;
        for (int i = 0; i < NTENTACLES; i++) {
            auto &tentacle = tentacles[i];
            if (tentacle.state == SLEEEP) {
                float len = glm::length(target - tentacle.end_coords);
                if (len < bestLen) {
                    bestIndex = i;
                    bestLen = len;
                }
            }
        }

        if (bestIndex != -1) {
            auto &tentacle = tentacles[bestIndex];
            tentacle.makeMove(target);
        }
    }

    for (auto &tentacle : tentacles) {
        tentacle.update(delta, coords);
    }
}

void Player::render(float elapsed) {
    float PI = glm::acos(0) * 2;
    float correcter = PI / 3;


    tentacle_shader->Use();
    glUniformMatrix4fv(u_ProjTrans, 1, GL_FALSE, glm::value_ptr(cam->proj));
    glUniform1i(u_FrameCount, FRAMECOUNT);
    glUniform1f(u_FrameTime, FRAMELENGTH);
    for (int i = 0; i < NTENTACLES; i++) {
        auto &tentacle = tentacles[i];
        glUniform1f(u_Time, tentacle.state == SLEEEP ? elapsed + i * 0.15f : 0.0f);
        float height = glm::length(tentacle.begin_coords - tentacle.end_coords);
        auto coords = (tentacle.begin_coords + tentacle.end_coords) * 0.5f;
        batch->draw(*tentacle_tex, u_ModelTrans, coords, height, 50, tentacle.getDynamicAngle());
    }

    //batch->draw(*tentacle_tex, u_ModelTrans, 0, 0, 200, 200);

    light_shader->Use();
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    batch->draw(*head, model_loc, coords.x, coords.y, HEAD_WIDTH, HEAD_HEIGHT);

    glUseProgram(0);
}

glm::vec2 Player::translateToGameCoords(glm::vec2 coords) {
    coords.x = coords.x / 2 * cam->getWidth();
    coords.y = coords.y / 2 * cam->getWidth();
    coords += cam->getPosition();
}

glm::vec2 Player::translateToGameCoords(float x, float y) {
    glm::vec2 coords;
    coords.x = x / 2 * cam->getWidth();
    coords.y = y / 2 * cam->getHeight();
    coords += cam->getPosition();
    return coords;
}

void *overlaps(glm::vec2 coords) {
    return nullptr;
}