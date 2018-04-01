//
// Created by opot on 01.04.18.
//
#include <GL/glew.h>
#include <iostream>

#include "Lizard.h"

Texture *Lizard::base, *Lizard::tail, *Lizard::slice;
Texture *base, *tail, *slice;
Shader *Lizard::shader;
GLint Lizard::u_ModelTrans;
GLint Lizard::u_ProjTrans;
GLint Lizard::u_FrameCount;
GLint Lizard::u_FrameTime;
GLint Lizard::u_Time;

Lizard::Lizard(glm::vec2 coord, Player *player, std::vector<GameObject *> *map) : GameObject(nullptr, x, y),
                                                                                  coord(coord), player(player),
                                                                                  state(READY) {}

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
    auto dist = player->coords - coord;
    auto vec = glm::normalize(dist);
    float angle = std::atan2(vec.y, vec.x) - PI / 2 + PI / 8;
    shader->Use();
    switch (state) {
        case PROCESS: {
            glUniformMatrix4fv(u_ProjTrans, 1, GL_FALSE, glm::value_ptr(cam->proj));
            glUniform1i(u_FrameCount, FRAMECOUNT_TAIL);
            glUniform1f(u_FrameTime, FRAMELENGTH_TAIL);
            glUniform1f(u_Time, reload);
            batch->draw(*slice, u_ModelTrans, coord, WIDTH, HEIGHT, angle);
            break;
        }

        default: {
            glUniformMatrix4fv(u_ProjTrans, 1, GL_FALSE, glm::value_ptr(cam->proj));
            glUniform1i(u_FrameCount, FRAMECOUNT);
            glUniform1f(u_FrameTime, FRAMELENGTH);
            glUniform1f(u_Time, elapsed);
            batch->draw(*base, u_ModelTrans, coord, WIDTH, HEIGHT, angle);
            break;

        }
    }
    glUseProgram(0);
}
