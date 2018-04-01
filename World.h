//
// Created by opot on 12.05.17.
//

#ifndef GLUTGL_WORLD_H
#define GLUTGL_WORLD_H

#include "GlUtils/Mesh.h"
#include "GlUtils/Texture.h"
#include "GlUtils/OrthographicCamera.h"
#include "GlUtils/SpriteBatch.h"
#include "GlUtils/Shader.h"
#include "environment/Terrain.h"

#include <glm/glm.hpp>

using fjfj::Mesh;
using fjfj::Texture;
using fjfj::Shader;
using fjfj::OrthographicCamera;
using fjfj::SpriteBatch;

class World {

    const float TERRAIN_CHANCE = 0.05;
    const float EXIT_CHANCE = 0.001;

    OrthographicCamera *cam;
    SpriteBatch *batch;

    Shader back_shader;
    Texture background;
    GLint proj_loc;
    GLint model_loc;

    StaticObject ***map;

public:
    static const int WORLD_SIZE = 30;
    static const int PART_SIZE = 80;
    static const int WORLD_WIDTH = 1440;
    static const int WORLD_HEIGHT = 920;

    World(SpriteBatch *batch, OrthographicCamera *cam);

    void update(float delta, float elapsed);

    void render(SpriteBatch *batch, OrthographicCamera *cam);
};


#endif //GLUTGL_WORLD_H