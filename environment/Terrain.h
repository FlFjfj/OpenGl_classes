//
// Created by opot on 01.04.18.
//

#ifndef GLUTGL_TERRAIN_H
#define GLUTGL_TERRAIN_H

#include "../GlUtils/Texture.h"
#include "../GlUtils/Shader.h"

using namespace fjfj;

class StaticObject {
    Texture *tex;

public:
    StaticObject(Texture *tex);

    virtual void update(float delta) = 0;
    virtual void draw(int x, int y) = 0;
};

class Terrain : public StaticObject {

public:
    Terrain(Texture *tex);

    virtual void update(float delta);
    virtual void draw(int x, int y);

    static Shader *TerrainShader;
};

class Exit : public StaticObject {
public:
    Exit(Texture *tex);

    virtual void update(float delta);
    virtual void draw(int x, int y);

    static Shader *exitShader;
};


#endif //GLUTGL_TERRAIN_H
