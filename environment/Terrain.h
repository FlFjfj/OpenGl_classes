//
// Created by opot on 01.04.18.
//

#ifndef GLUTGL_TERRAIN_H
#define GLUTGL_TERRAIN_H

#include "../GlUtils/Texture.h"
#include "../GlUtils/Shader.h"
#include "../GlUtils/SpriteBatch.h"
#include "../GlUtils/OrthographicCamera.h"

using namespace fjfj;

class StaticObject {
public:
    Texture *tex;

    StaticObject(Texture *tex);

    virtual void update(float delta, float elapsed) = 0;

    virtual void draw(SpriteBatch *batch, OrthographicCamera *cam, int x, int y) = 0;
};

class Terrain : public StaticObject {

public:
    Terrain(Texture *tex);

    virtual void update(float delta, float elapsed);

    virtual void draw(SpriteBatch *batch, OrthographicCamera *cam, int x, int y);

    static Shader *TerrainShader;
    static GLint model_loc;
    static GLint proj_loc;
};

class Exit : public StaticObject {
public:
    Exit(Texture *tex);

    virtual void update(float delta, float elapsed);

    virtual void draw(SpriteBatch *batch, OrthographicCamera *cam, int x, int y);

    static Shader *exitShader;
    static GLint u_ModelTrans;
    static GLint u_ProjTrans;
    static GLint u_FrameCount;
    static GLint u_FrameTime;
    static GLint u_Time;

    const int FRAMECOUNT = 7;
    const float FRAMELENGTH = 0.3;
};


#endif //GLUTGL_TERRAIN_H
