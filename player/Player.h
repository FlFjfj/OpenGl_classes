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

using namespace fjfj;

enum TentacleState {
    SLEEEP, MOVE, CONNECTED
};

struct Tentacle {
    float angle;
    TentacleState state;
    glm::vec2 begin_coords;
    glm::vec2 end_coords;
    bool push;
    glm::vec2 target;
    float speed;
    const float BASIC_ACC = -500;
    const float BASIC_SPEED = 500;
    const float BASIC_LENGTH = 130;

    void makeMove(glm::vec2 target) {
        this->target = target;
        state = MOVE;
        speed = BASIC_SPEED;
        push = false;
    }

    void update(float delta, glm::vec2 base) {
        switch (state) {
            case SLEEEP:
                begin_coords = base;
                end_coords = begin_coords + getOffset();
                break;

            case MOVE:
                begin_coords = base;
                speed += BASIC_ACC * delta;
                end_coords += glm::normalize(end_coords - target) * delta * speed;
                if (glm::length(begin_coords - end_coords) < 1) {
                    state = SLEEEP;
                    end_coords = base + getOffset();
                }

                break;

            default:
                break;
        }
    }

    glm::vec2 getOffset() {
        return float(BASIC_LENGTH) * glm::vec2(glm::cos(angle), glm::sin(angle));
    }
};

class Player {
    const static uint32_t NTENTACLES = 8;
    const static uint32_t TENTACLE_OFFSET = 30;
    const static uint32_t HEAD_WIDTH = 100;
    const static uint32_t HEAD_HEIGHT = 100;
    const static uint32_t TENTACLE_WIDTH = 100;
    const static uint32_t TENTACLE_HEIGHT = 50;

    Texture *head;
    Texture *tentacle_tex;
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

    GLint u_ModelTrans;
    GLint u_ProjTrans;
    GLint u_FrameCount;
    GLint u_FrameTime;
    GLint u_Time;

    const int FRAMECOUNT=7;
    const float FRAMELENGTH=0.3;
    float elapsed = 0;
    glm::vec2 translateToGameCoords(glm::vec2 coords);

    glm::vec2 translateToGameCoords(float x, float y);

    glm::vec2 getTentacleOffset(float angle);

public:
    Player(PlayerController *controller, SpriteBatch *batch, OrthographicCamera *cam);

    void update(float delta);

    void render();

    void *overlaps(glm::vec2 coords);
};


#endif //GLUTGL_PLAYER_H
