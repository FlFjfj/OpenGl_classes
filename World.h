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
#include "player/Player.h"

#include <glm/glm.hpp>
#include <vector>

using fjfj::Mesh;
using fjfj::Texture;
using fjfj::Shader;
using fjfj::OrthographicCamera;
using fjfj::SpriteBatch;

class World {
public:
    const float TERRAIN_CHANCE = 0.05;
    const float EXIT_CHANCE = 0.03;

    OrthographicCamera *cam;
    SpriteBatch *batch;
    Player *player;

    Shader back_shader;
    Texture background;
    GLint proj_loc;
    GLint model_loc;
    GLint time_loc;

    std::vector<GameObject*> map;

    static const int WORLD_SIZE = 30;
    static const int PART_SIZE = 150;
    static const int WORLD_WIDTH = 1920;
    static const int WORLD_HEIGHT = 1080;

    World(SpriteBatch *batch, OrthographicCamera *cam, Player *player);

    void update(float delta);

    void render(SpriteBatch *batch, OrthographicCamera *cam, float elapsed);
};


#endif //GLUTGL_WORLD_H