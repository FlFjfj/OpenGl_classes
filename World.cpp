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
            if (dist(gen) <= this->TERRAIN_CHANCE) {
                map[i][j] = new Terrain(terrainTex);
                continue;
            }

            if (dist(gen) <= this->TERRAIN_CHANCE + this->EXIT_CHANCE) {
                map[i][j] = new Exit(terrainTex);
                continue;
            }

            map[i][j] = nullptr;
        }
    }
}

void World::update(float delta) {

}

void World::render() {
    back_shader.Use();
    int size = this->PART_SIZE * this->WORLD_SIZE;
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    batch->draw(this->background, this->model_loc, 0, 0, size, size);
    glUseProgram(0);


}