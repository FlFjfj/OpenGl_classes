//
// Created by opot on 12.05.17.
//

#include "World.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "GlUtils/MeshLoader.h"

World::World(SpriteBatch *batch, OrthographicCamera *cam) : background("texture/background.jpg"), batch(batch),
                                                            cam(cam),
                                                            back_shader("shader/back.vert", "shader/back.frag") {
    model_loc = glGetUniformLocation(back_shader.Program, "u_ModelTrans");
    proj_loc = glGetUniformLocation(back_shader.Program, "u_ProjTrans");
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