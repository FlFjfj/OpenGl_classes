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

World::World(SpriteBatch *batch, OrthographicCamera *cam) : background("texture/background.png"), batch(batch),
                                                            cam(cam),
                                                            back_shader("shader/back.vert", "shader/back.frag") {
    model_loc = glGetUniformLocation(back_shader.Program, "u_ModelTrans");
    proj_loc = glGetUniformLocation(back_shader.Program, "u_ProjTrans");

    Terrain::TerrainShader = new Shader("shader/light.vert", "shader/light.frag");
    Terrain::model_loc = glGetUniformLocation(Terrain::TerrainShader->Program, "u_ModelTrans");
    Terrain::proj_loc = glGetUniformLocation(Terrain::TerrainShader->Program, "u_ProjTrans");

    Exit::exitShader = new Shader("shader/animated.vert", "shader/animated.frag");
    Exit::u_ModelTrans = glGetUniformLocation(Exit::exitShader->Program, "u_ModelTrans");
    Exit::u_ProjTrans = glGetUniformLocation(Exit::exitShader->Program, "u_ProjTrans");
    Exit::u_FrameCount = glGetUniformLocation(Exit::exitShader->Program, "u_FrameCount");
    Exit::u_FrameTime = glGetUniformLocation(Exit::exitShader->Program, "u_FrameTime");
    Exit::u_Time = glGetUniformLocation(Exit::exitShader->Program, "u_Time");

    Texture *terrainTex = new Texture("texture/corall.png");
    Texture *exitTex = new Texture("texture/exit.png");

    std::random_device device;
    std::mt19937 gen(unsigned(std::time(0)));
    std::uniform_real_distribution<> dist(0, 1);

    map = new StaticObject **[this->WORLD_SIZE];
    for (int i = 0; i < this->WORLD_SIZE; i++) {
        map[i] = new StaticObject *[this->WORLD_SIZE]();
        for (int j = 0; j < this->WORLD_SIZE; j++) {
            double val = dist(gen);
            if (val <= this->TERRAIN_CHANCE && i > 0 & i < World::WORLD_SIZE - 1 && j > 0 & j < World::WORLD_SIZE - 1 &&
                i != World::WORLD_SIZE / 2 && i != World::WORLD_SIZE / 2 + 1 && j != World::WORLD_SIZE / 2 &&
                j != World::WORLD_SIZE / 2 + 1) {
                map[i][j] = new Terrain(terrainTex);
                continue;
            }

            if (val <= this->TERRAIN_CHANCE + this->EXIT_CHANCE && i > 0 & i < World::WORLD_SIZE - 1 &&
                j > 0 & j < World::WORLD_SIZE - 1 &&
                i != World::WORLD_SIZE / 2 && i != World::WORLD_SIZE / 2 + 1 && j != World::WORLD_SIZE / 2 &&
                j != World::WORLD_SIZE / 2 + 1) {
                map[i][j] = new Exit(exitTex);
                continue;
            }

            map[i][j] = nullptr;
        }
    }
}

void World::update(float delta) {
    for (int i = 0; i < this->WORLD_SIZE; i++) {
        for (int j = 0; j < this->WORLD_SIZE; j++) {
            if (map[i][j] != nullptr) {
                map[i][j]->update(delta);
            }
        }
    }
}

void World::render(SpriteBatch *batch, OrthographicCamera *cam, float elapsed) {
    back_shader.Use();
    int size = this->PART_SIZE * this->WORLD_SIZE;
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    batch->draw(this->background, this->model_loc, 0, 0, size, size);
    glUseProgram(0);

    for (int i = 0; i < World::WORLD_SIZE; i++) {
        for (int j = 0; j < World::WORLD_SIZE; j++) {
            if (map[i][j] != nullptr) {
                map[i][j]->draw(batch, cam, elapsed, i, j);
            }
        }
    }
}