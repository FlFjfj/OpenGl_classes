//
// Created by opot on 01.04.18.
//
#include <GL/glew.h>
#include <iostream>

#include "Lizard.h"

Lizard::Lizard(glm::vec2 coord, Player *player, std::vector<GameObject *> *map) : GameObject(nullptr, x, y), coord(coord), player(player),
                                                                                  speed({0, 0}), map(map), reload(0),
                                                                                  state(READY) {
    base = new Texture("texture/lizard.png");
    tail = new Texture("texture/tail.png");
    slice = new Texture("texture/tailshot.png");

    shader = new Shader("shader/animated.vert", "shader/animated.frag");

    u_ModelTrans = glGetUniformLocation(shader->Program, "u_ModelTrans");
    u_ProjTrans = glGetUniformLocation(shader->Program, "u_ProjTrans");
    u_FrameCount = glGetUniformLocation(shader->Program, "u_FrameCount");
    u_FrameTime = glGetUniformLocation(shader->Program, "u_FrameTime");
    u_Time = glGetUniformLocation(shader->Program, "u_Time");

    //tail_shader = new Shader("shader/tail.vert", "shader/tail.frag");
}

void Lizard::update(float delta) {
    //check anim
    coord += speed * delta;
    if (glm::length(speed) > 0.001) {
        float newlen = (glm::length(speed) - ACC * delta);
        if (newlen < 0) {
            speed = {0, 0};
        } else {
            speed = glm::normalize(speed) * newlen;
        }
    }

    switch (state) {
        case RELOAD: {
            reload -= delta;
            if (reload <= 0)
                state = READY;
            break;
        }
        case PROCESS: {
            reload += delta;
            if (reload >= FRAMECOUNT_TAIL * FRAMELENGTH_TAIL) {
                reload = SHOT_SPEED;
                state = RELOAD;
                //create instance of tail;
            }
            break;
        }
        default:
            break;
    }

    x = coord.x;
    y = coord.y;

    auto dist = coord - player->coords;
    if (glm::length(dist) < MIN_DIST) {
        speed += glm::normalize(dist) * delta * SPEED;
        return;
    }

    if (glm::length(dist) > MAX_DIST) {
        speed -= glm::normalize(dist) * delta * SPEED;
        return;
    }

    if (state == READY) {
        state = PROCESS;
        reload = 0;
    }

}

void Lizard::draw(SpriteBatch *batch, OrthographicCamera *cam, float elapsed) {
    float PI = glm::acos(0) * 2;
    shader->Use();
    switch (state) {
        case PROCESS: {
            glUniformMatrix4fv(u_ProjTrans, 1, GL_FALSE, glm::value_ptr(cam->proj));
            glUniform1i(u_FrameCount, FRAMECOUNT_TAIL);
            glUniform1f(u_FrameTime, FRAMELENGTH_TAIL);
            glUniform1f(u_Time, reload);
            auto vec = glm::normalize(speed);
            float angle = std::atan2(speed.y, speed.x) - PI / 4;
            batch->draw(*slice, u_ModelTrans, coord, WIDTH, HEIGHT, angle);
            break;
        }

        default: {
            glUniformMatrix4fv(u_ProjTrans, 1, GL_FALSE, glm::value_ptr(cam->proj));
            glUniform1i(u_FrameCount, FRAMECOUNT);
            glUniform1f(u_FrameTime, FRAMELENGTH);
            glUniform1f(u_Time, elapsed);
            auto vec = glm::normalize(speed);
            float angle = std::atan2(speed.y, speed.x) - PI / 4;
            batch->draw(*base, u_ModelTrans, coord, WIDTH, HEIGHT, angle);
            break;

        }
    }
    glUseProgram(0);
}
