//
// Created by opot on 01.04.18.
//

#ifndef GLUTGL_LIZARD_H
#define GLUTGL_LIZARD_H


#include <glm/vec2.hpp>
#include "../GameState/GameOver.h"
#include "../GlUtils/Texture.h"
#include "../GlUtils/Shader.h"
#include "../player/Player.h"

using namespace fjfj;

class Lizard : public GameObject {

    enum LizState {
        READY, PROCESS, RELOAD
    };

    const float WIDTH = 100;
    const float HEIGHT = 150;
    const float MIN_DIST = 400;
    const float MAX_DIST = 600;
    const float ACC = 300;
    const float SPEED = 600;
    const float SHOT_SPEED = 3;

    float reload;
    LizState state;

    glm::vec2 coord;
    glm::vec2 speed;

    Texture *base, *tail, *slice;

    Shader *shader;
    GLint u_ModelTrans;
    GLint u_ProjTrans;
    GLint u_FrameCount;
    GLint u_FrameTime;
    GLint u_Time;

    const int FRAMECOUNT = 5;
    const float FRAMELENGTH = 0.2;
    const int FRAMECOUNT_TAIL = 3;
    const float FRAMELENGTH_TAIL = 0.3;

    Shader *tail_shader;
    GLint proj_loc;
    GLint model_loc;
    std::vector<GameObject *> *map;
    Player *player;

public:
    Lizard(glm::vec2 coord, Player *player, std::vector<GameObject *> *map);

    void update(float delta) override;

    void draw(SpriteBatch *batch, OrthographicCamera *cam, float elapsed) override;
};


#endif //GLUTGL_LIZARD_H
