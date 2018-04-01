
#include <iostream>
#include "../GlUtils/MeshLoader.h"

#include "Player.h"
#include "../GlUtils/OrthographicCamera.h"
#include "PlayerController.h"
#include "../World.h"
#include "../GameState/ProgramBase.h"
#include "../GameState/GameOver.h"
#include "../GameState/MainGame.h"

#include <random>
#include <ctime>

Player::Player(PlayerController *controller, SpriteBatch *batch, OrthographicCamera *cam,
               std::vector<StaticObject *> *map)
        : controller(controller),
          batch(batch), cam(cam), map(map) {
    head = new Texture("texture/head.png");
    tentacle_tex = new Texture *[2];
    tentacle_tex[0] = new Texture("texture/tenta1.png");
    tentacle_tex[1] = new Texture("texture/tenta2.png");
    light_shader = new Shader("shader/light.vert", "shader/light.frag");
    tentacle_shader = new Shader("shader/tenta.vert", "shader/tenta.frag");
    model_loc = glGetUniformLocation(light_shader->Program, "u_ModelTrans");
    proj_loc = glGetUniformLocation(light_shader->Program, "u_ProjTrans");

    u_ModelTrans = glGetUniformLocation(tentacle_shader->Program, "u_ModelTrans");
    u_ProjTrans = glGetUniformLocation(tentacle_shader->Program, "u_ProjTrans");
    u_FrameCount = glGetUniformLocation(tentacle_shader->Program, "u_FrameCount");
    u_FrameTime = glGetUniformLocation(tentacle_shader->Program, "u_FrameTime");
    u_Time = glGetUniformLocation(tentacle_shader->Program, "u_Time");
    std::mt19937 gen(unsigned(std::time(0)));
    std::uniform_int_distribution<> dist(0, 1);

    float PI = glm::acos(0) * 2;
    for (int i = 0; i < NTENTACLES; i++) {
        auto &tentacle = tentacles[i];
        tentacle.angle = 0.25f * i * PI;
        tentacle.begin_coords = {0, 0};
        tentacle.end_coords = {0, 0};
        tentacle.speed = 0;
        tentacle.state = SLEEEP;
        tentacle.texIndex = dist(gen);
    }

    coords = {0, 0};
    vertical_speed = {0, 300};
    horizontal_speed = {300, 0};
    speed = {-1, -1};
}

void Player::update(float delta, float elapsed) {
    //coords += speed*delta;
    //speed -= glm::normalize(speed)*PLAYER_ACC*delta;
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

    if(controller->unconnectAll()) {
        for (auto &tentacle : tentacles) {
            if(tentacle.state == CONNECTED) {
                tentacle.returnEnd();
            }
        }
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

    const int delta_stip = 100;

    if (coords.x - delta_stip < -maxsize / 2) {
        coords.x = -maxsize / 2 + delta_stip;
        speed.x = -speed.x;
    }

    if (coords.x + delta_stip > maxsize / 2) {
        coords.x = maxsize / 2 - delta_stip;
        speed.x = -speed.x;
    }

    if (coords.y - delta_stip < -maxsize / 2) {
        coords.y = -maxsize / 2 + delta_stip;
        speed.y = -speed.y;
    }

    if (coords.y + delta_stip > maxsize / 2) {
        coords.y = maxsize / 2 - delta_stip;
        speed.y = -speed.y;
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
            std::cout << (e.type == M_RELEASE_LEFT) << std::endl;
            tentacle.makeMove(target, e.type == M_RELEASE_LEFT);
        }
    }

    auto obj = getCollision(coords);
    if (obj != nullptr && obj->getType() == 1) {
        ProgramBase::changeState(ProgramBase::DEAD);
        GameOver::setScore(elapsed);
    }

    if (glm::length(speed) > 0.001) {
        float newlen = (glm::length(speed) - PLAYER_ACC * delta);
        if (newlen < 0) {
            speed = {0, 0};
        } else {
            speed = glm::normalize(speed) * newlen;
        }
    }

    for (auto &tentacle : tentacles) {
        auto obj = getCollision(tentacle.end_coords);
        if (obj != nullptr) {
            if (obj->getType() == 0 && tentacle.state == MOVE) {
                if (tentacle.push) {
                    speed += glm::normalize(coords - tentacle.end_coords) * 300.0f;
                    tentacle.returnEnd();
                } else {
                   // speed -= glm::normalize(coords - tentacle.end_coords) * 500.00f;
                    tentacle.connectEnd();
                }
            }
        }

        if(tentacle.state == CONNECTED) {
            speed -= glm::normalize(coords - tentacle.end_coords)*1000.00f*delta;
        }

        tentacle.update(delta, coords);
    }

    coords += speed * delta;
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
        batch->draw(*tentacle_tex[tentacle.texIndex], u_ModelTrans, coords, height, 50, tentacle.getDynamicAngle());
    }

    //batch->draw(*tentacle_tex, u_ModelTrans, 0, 0, 200, 200);

    light_shader->Use();
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    auto vec= glm::normalize(speed);
    float angle = std::atan2(speed.y,speed.x) - PI/2;
    batch->draw(*head, model_loc, coords.x, coords.y, HEAD_WIDTH, HEAD_HEIGHT, angle);

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

StaticObject *Player::getCollision(glm::vec2 coords) {
    float COLLISIONBOUND = World::PART_SIZE / 2;
    for (auto el : *map) {
        glm::vec2 objc = {el->x, el->y};
        if (glm::length(coords - objc) < COLLISIONBOUND) {
            return el;
        }
    }

    return nullptr;
}