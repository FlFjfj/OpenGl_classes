//
// Created by opot on 12.05.17.
//

#include "World.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <random>
#include <ctime>

#include "GlUtils/MeshLoader.h"
#include "environment/Lizard.h"

std::mt19937 gen(unsigned(std::time(0)));
std::uniform_real_distribution<> dist(0, 1);

double genNumber() {
    return dist(gen);
}

World::World(SpriteBatch *batch, OrthographicCamera *cam, Player *player) : background("texture/background.png"),
                                                                            batch(batch), player(player),
                                                                            cam(cam),
                                                                            back_shader("shader/back.vert",
                                                                                        "shader/back.frag") {
    model_loc = glGetUniformLocation(back_shader.Program, "u_ModelTrans");
    proj_loc = glGetUniformLocation(back_shader.Program, "u_ProjTrans");
    time_loc = glGetUniformLocation(back_shader.Program, "u_Time");

    Terrain::TerrainShader = new Shader("shader/StaticObject.vert", "shader/StaticObject.frag");
    Terrain::u_ModelTrans = glGetUniformLocation(Terrain::TerrainShader->Program, "u_ModelTrans");
    Terrain::u_ProjTrans = glGetUniformLocation(Terrain::TerrainShader->Program, "u_ProjTrans");
    Terrain::u_FrameCount = glGetUniformLocation(Terrain::TerrainShader->Program, "u_FrameCount");
    Terrain::u_FrameTime = glGetUniformLocation(Terrain::TerrainShader->Program, "u_FrameTime");
    Terrain::u_Time = glGetUniformLocation(Terrain::TerrainShader->Program, "u_Time");

    Exit::exitShader = new Shader("shader/StaticObject.vert", "shader/StaticObject.frag");
    Exit::u_ModelTrans = glGetUniformLocation(Exit::exitShader->Program, "u_ModelTrans");
    Exit::u_ProjTrans = glGetUniformLocation(Exit::exitShader->Program, "u_ProjTrans");
    Exit::u_FrameCount = glGetUniformLocation(Exit::exitShader->Program, "u_FrameCount");
    Exit::u_FrameTime = glGetUniformLocation(Exit::exitShader->Program, "u_FrameTime");
    Exit::u_Time = glGetUniformLocation(Exit::exitShader->Program, "u_Time");

    Texture *terrainTex = new Texture("texture/corall.png");
    Texture *exitTex = new Texture("texture/exit.png");

    float world_size = World::WORLD_SIZE * World::PART_SIZE;

    for (int i = 0; i < World::WORLD_SIZE * World::WORLD_SIZE; i++) {
        double val = genNumber();
        if (val <= this->TERRAIN_CHANCE) {
            float x = (genNumber() - 0.5f) * (world_size - 200);
            float y = (genNumber() - 0.5f) * (world_size - 200);
            map.push_back(new Terrain(terrainTex, x, y, genNumber));
            continue;
        }

        if (val <= this->TERRAIN_CHANCE + this->EXIT_CHANCE) {
            float x = (genNumber() - 0.5f) * (world_size - 200);
            float y = (genNumber() - 0.5f) * (world_size - 200);
            map.push_back(new Exit(exitTex, x, y, genNumber));
            continue;
        }
    }
}

void World::update(float delta) {
    for (auto el: map) {
        el->update(delta);
    }
}

void World::render(SpriteBatch *batch, OrthographicCamera *cam, float elapsed) {
    back_shader.Use();
    int size = this->PART_SIZE * this->WORLD_SIZE;
    glUniform1f(time_loc, elapsed);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    batch->draw(this->background, this->model_loc, 0, 0, size, size);
    glUseProgram(0);

    for (auto el: map) {
        el->draw(batch, cam, elapsed);
    }
}
