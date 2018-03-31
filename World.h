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

#include <glm/glm.hpp>

using fjfj::Mesh;
using fjfj::Texture;
using fjfj::Shader;
using fjfj::OrthographicCamera;
using fjfj::SpriteBatch;

class World {

    const int WORLD_SIZE = 50;
    const int PART_SIZE = 50;

    OrthographicCamera *cam;
    SpriteBatch *batch;

    Shader back_shader;
    Texture background;
    GLint proj_loc;
    GLint model_loc;

public:
    World(SpriteBatch *batch, OrthographicCamera *cam);

    void update(float delta);

    void render();
};


#endif //GLUTGL_WORLD_H