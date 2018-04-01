//
// Created by user on 01.04.18.
//

#include <iostream>
#include "Tail.h"

Shader *Tail::shader = nullptr;
Texture *Tail::texture = nullptr;

Tail::Tail(glm::vec2 coords, glm::vec2 basespeed, Player *player, std::vector<GameObject *> *map) : GameObject(nullptr,
                                                                                                               coords.x,
                                                                                                               coords.y),
                                                                                                    coords(coords),
                                                                                                    speed(basespeed),
                                                                                                    player(player),
                                                                                                    map(map) {
    elapsed = 0;
}

void Tail::update(float delta) {
    lifetime += delta;
    coords += speed * delta;
    x = coords.x;
    y = coords.y;
    auto dist = player->coords - coords;
    if (glm::length(dist) < 100) {
        player->speed += 2.0f*speed;
        player->unconnectAll();
        for (auto it = map->begin(); it != map->end(); ++it) {
            if (*it == this) {
                map->erase(it);
                return;
            }
        }
    }

    if (lifetime >= TIMETOLIVE) {
        for (auto it = map->begin(); it != map->end(); ++it) {
            if (*it == this) {
                map->erase(it);
                return;
            }
        }
    }
}

void Tail::draw(SpriteBatch *batch, OrthographicCamera *cam, float elapsed) {

    this->elapsed = elapsed;
    shader->Use();
    GLint proj_loc = glGetUniformLocation(shader->Program, "u_ProjTrans");
    GLint model_loc = glGetUniformLocation(shader->Program, "u_ModelTrans");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    float PI = glm::acos(0) * 2;
    float angle = std::atan2(speed.y, speed.x) - PI / 2;

    batch->draw(*texture, model_loc, coords.x, coords.y, 70, 70, angle);
    glUseProgram(0);
}

int Tail::getType() {
    return 10;
}