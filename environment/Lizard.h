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
public:
    enum LizState {
        READY, PROCESS, RELOAD
    };

    const float WIDTH = 150;
    const float HEIGHT = 200;
    const float MIN_DIST = 300;
    const float MAX_DIST = 400;
    const float ACC = 300;
    const float SPEED = 450;
    const float SHOT_SPEED = 2;

    float reload;
    LizState state;

    glm::vec2 coord;
    glm::vec2 speed;

    const int FRAMECOUNT = 5;
    const float FRAMELENGTH = 0.5;
    const int FRAMECOUNT_TAIL = 3;
    const float FRAMELENGTH_TAIL = 0.4;

    std::vector<GameObject *> *map;
    Player *player;


    Lizard(glm::vec2 coord, Player *player, std::vector<GameObject *> *map);

    void update(float delta) override;

    void draw(SpriteBatch *batch, OrthographicCamera *cam, float elapsed) override;

    int getType() override { return 9; }
    GameObject* getCollision(glm::vec2 coords);

    static Texture *base, *tail, *slice;
    static Shader *shader;
    static GLint u_ModelTrans;
    static GLint u_ProjTrans;
    static GLint u_FrameCount;
    static GLint u_FrameTime;
    static GLint u_Time;

};


#endif //GLUTGL_LIZARD_H
