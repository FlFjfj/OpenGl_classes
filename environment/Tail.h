//
// Created by user on 01.04.18.
//

#ifndef GLUTGL_TAIL_H
#define GLUTGL_TAIL_H


#include <vector>
#include "GameObject.h"
#include "../GlUtils/Shader.h"
#include "../player/Player.h"

class Tail : public GameObject {
public:
    static Shader *shader;
    static Texture *texture;
    float elapsed;
    glm::vec2 coords;
    glm::vec2 speed;
    Player* player;
    const float selfspeed = 300;
    std::vector<GameObject *> *map;
    const float TIMETOLIVE = 2;

    Tail(glm::vec2 coords, glm::vec2 basespeed, Player* player, std::vector<GameObject*>* map);

    virtual void update(float delta) override;

    virtual void draw(SpriteBatch *batch, OrthographicCamera *cam, float elapsed) override;

    virtual int getType() override;
};


#endif //GLUTGL_TAIL_H
