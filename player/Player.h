//
// Created by opot on 23.04.17.
//

#ifndef GLUTGL_PLAYER_H
#define GLUTGL_PLAYER_H

#include <GL/glew.h>

#include "../GlUtils/Mesh.h"
#include "../GlUtils/Texture.h"
#include "PlayerController.h"
#include "../GlUtils/SpriteBatch.h"
#include "../GlUtils/Shader.h"
#include "../GlUtils/OrthographicCamera.h"
#include "../environment/Terrain.h"
#include <cmath>

using namespace fjfj;

enum TentacleState {
    SLEEEP, MOVE, RETURN, CONNECTED
};

struct Tentacle {
    float angle;
    int texIndex;
    TentacleState state;
    glm::vec2 begin_coords;
    glm::vec2 end_coords;
    bool push;
    glm::vec2 target;
    float speed;
    const float BASIC_ACC = -3000;
    const float BASIC_SPEED = 2000;
    const float BASIC_LENGTH = 100;

    void makeMove(glm::vec2 target, bool push) {
        this->target = glm::normalize(target - end_coords);
        state = MOVE;
        speed = BASIC_SPEED;
        this->push = push;
    }

    void returnEnd() {
        speed = 0;
        state = RETURN;
    }

    void connectEnd() {
        state = CONNECTED;
        speed = 0;
    }

    void update(float delta, glm::vec2 base) {
        begin_coords = base;
        switch (state) {
            case SLEEEP:
                end_coords = begin_coords + getOffset();
                break;

            case MOVE:
                speed += BASIC_ACC * delta;
                if (speed > 0) {
                    end_coords += target * delta * speed;
                } else {
                    state = RETURN;
                    break;
                }

                if (glm::length(begin_coords - end_coords) < BASIC_LENGTH) {
                    state = SLEEEP;
                    end_coords = base + getOffset();
                }

                break;

            case CONNECTED:
                if (glm::length(begin_coords - end_coords) < BASIC_LENGTH) {
                    state = SLEEEP;
                    end_coords = base + getOffset();
                }

                if (glm::length(begin_coords - end_coords) > 5 * BASIC_LENGTH) {
                    state = RETURN;
                    speed = -1;
                    //end_coords = base + getOffset();
                }

                break;

            case RETURN:
                speed += delta * BASIC_ACC;
                end_coords += glm::normalize(end_coords - begin_coords) * delta * speed;
                if (glm::length(begin_coords - end_coords) < BASIC_LENGTH) {
                    state = SLEEEP;
                    end_coords = base + getOffset();
                }

                break;

            default:
                break;
        }
    }

    void collide(StaticObject *obj) {

    }

    glm::vec2 getOffset() {
        return float(BASIC_LENGTH) * glm::vec2(glm::cos(angle), glm::sin(angle));
    }


    float getDynamicAngle() {
        auto vec = glm::normalize(end_coords - begin_coords);
        return std::atan2(vec.y, vec.x);
    }

    static void logvec2(const char *name, glm::vec2 vec) {
        std::cout << name << " " << vec.x << " " << vec.y << std::endl;
    }
};

class Player {
    const static uint32_t NTENTACLES = 8;
    const static uint32_t TENTACLE_OFFSET = 30;
    const static uint32_t HEAD_WIDTH = 100;
    const static uint32_t HEAD_HEIGHT = 100;
    const static uint32_t CAMRAD = 300;

    Texture *head;
    Texture **tentacle_tex;
    GLint proj_loc;
    GLint model_loc;
    Shader *light_shader;
    Shader *tentacle_shader;
    PlayerController *controller;
    SpriteBatch *batch;
    OrthographicCamera *cam;


    glm::vec2 coords;
    Tentacle tentacles[NTENTACLES];
    glm::vec2 vertical_speed;
    glm::vec2 horizontal_speed;
    glm::vec2 speed;
    const float PLAYER_ACC = 500;

    GLint u_ModelTrans;
    GLint u_ProjTrans;
    GLint u_FrameCount;
    GLint u_FrameTime;
    GLint u_Time;

    const int FRAMECOUNT = 7;
    const float FRAMELENGTH = 0.3;
    //float elapsed = 0;

    std::vector<StaticObject *> *map;

    glm::vec2 translateToGameCoords(glm::vec2 coords);

    glm::vec2 translateToGameCoords(float x, float y);

    glm::vec2 getTentacleOffset(float angle);

public:
    Player(PlayerController *controller, SpriteBatch *batch, OrthographicCamera *cam, std::vector<StaticObject *> *map);

    void update(float delta, float elapsed);

    void render(float elapsed);

    StaticObject *getCollision(glm::vec2 coords);
};


#endif //GLUTGL_PLAYER_H
