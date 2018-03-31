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
    ONE, TWO
};

class Player {
    const static uint32_t NTENTACLES = 8;
    const static uint32_t TENTACLE_OFFSET=30;
    const static uint32_t HEAD_WIDTH = 100;
    const static uint32_t HEAD_HEIGHT = 100;
    const static uint32_t TENTACLE_WIDTH = 100;
    const static uint32_t TENTACLE_HEIGHT = 100;

    Texture *head;
    Texture *tentacle;
    GLint proj_loc;
    GLint model_loc;
    Shader *shader;
    PlayerController *controller;
    SpriteBatch *batch;
    TentacleState tentacles[NTENTACLES];
    float tentacleAngle[NTENTACLES];
    OrthographicCamera *cam;

    glm::vec2 coords;
    glm::vec2 tentacleOffsets[NTENTACLES];
    glm::vec2 vertical_speed;
    glm::vec2 horizontal_speed;


public:
    Player(PlayerController *controller, SpriteBatch *batch, OrthographicCamera *cam);

    void update(float delta);

    void render();

};


#endif //GLUTGL_PLAYER_H
