//
// Created by opot on 01.04.18.
//

#ifndef GLUTGL_GAMEOBJECT_H
#define GLUTGL_GAMEOBJECT_H


#include "../GlUtils/Texture.h"
#include "../GlUtils/SpriteBatch.h"
#include "../GlUtils/OrthographicCamera.h"

using namespace fjfj;

class GameObject {
public:
    Texture *tex;
    float x, y;

    explicit GameObject(Texture *tex, float x, float y);

    virtual void update(float delta) = 0;

    virtual void draw(SpriteBatch *batch, OrthographicCamera *cam, float elapsed) = 0;

    virtual int getType() = 0;
};


#endif //GLUTGL_GAMEOBJECT_H
