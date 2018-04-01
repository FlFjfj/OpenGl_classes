
#include <iostream>
#include "../GlUtils/MeshLoader.h"

#include "Player.h"
#include "../GlUtils/OrthographicCamera.h"
#include "PlayerController.h"


Player::Player(PlayerController *controller, SpriteBatch *batch, OrthographicCamera *cam)
        : controller(controller),
          batch(batch), cam(cam) {
    head = new Texture("texture/head.png");
    tentacle_tex = new Texture("texture/tenta1.png");
    light_shader = new Shader("shader/light.vert", "shader/light.frag");
    tentacle_shader = new Shader("shader/animated.vert", "shader/animated.frag");
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
        tentacle.end_coords = getTentacleOffset(tentacle.angle);
        tentacle.speed = 0;
        tentacle.state = SLEEEP;

    }

    coords = {0, 0};
    vertical_speed = {0, 100};
    horizontal_speed = {100, 0};
}

void Player::update(float delta) {
    elapsed += delta;
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
            std::cout << "index " << bestIndex << "target x " << target.x << " y " << target.y << std::endl;
            tentacle.makeMove(target);
        }
    }

    for (auto &tentacle : tentacles) {
        tentacle.update(delta, coords);
    }
}

void Player::render() {
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

glm::vec2 Player::getTentacleOffset(float angle) {
    return float(TENTACLE_OFFSET) * glm::vec2(glm::cos(angle), glm::sin(angle));
}

void *overlaps(glm::vec2 coords) {
    return nullptr;
}