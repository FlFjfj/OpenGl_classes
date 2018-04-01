//
// Created by opot on 01.04.18.
//

#include "Terrain.h"
#include "../World.h"

#include <iostream>

StaticObject::StaticObject(Texture *tex) : tex(tex) {}

Shader *Terrain::TerrainShader = nullptr;
GLint Terrain::model_loc = 0;
GLint Terrain::proj_loc = 0;

Terrain::Terrain(Texture *tex) : StaticObject(tex) {}

void Terrain::draw(SpriteBatch *batch, OrthographicCamera *cam, float elapsed, int x, int y) {
    Terrain::TerrainShader->Use();
    glUniformMatrix4fv(Terrain::proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    batch->draw(*this->tex, Terrain::model_loc, (x - World::WORLD_SIZE / 2.0f) * World::PART_SIZE,
                (y - World::WORLD_SIZE / 2.0f) * World::PART_SIZE, World::PART_SIZE, World::PART_SIZE);
    glUseProgram(0);
}

void Terrain::update(float delta) {}

Shader *Exit::exitShader = nullptr;
GLint Exit::u_ModelTrans = 0;
GLint Exit::u_ProjTrans = 0;
GLint Exit::u_FrameCount = 0;
GLint Exit::u_FrameTime = 0;
GLint Exit::u_Time = 0;


Exit::Exit(Texture *tex) : StaticObject(tex) {}

void Exit::draw(SpriteBatch *batch, OrthographicCamera *cam, float elapsed, int x, int y) {
    Exit::exitShader->Use();
    glUniformMatrix4fv(u_ProjTrans, 1, GL_FALSE, glm::value_ptr(cam->proj));
    glUniform1i(u_FrameCount, FRAMECOUNT);
    glUniform1f(u_FrameTime, FRAMELENGTH);
    glUniform1f(u_Time, elapsed);
    batch->draw(*this->tex, u_ModelTrans, (x - World::WORLD_SIZE / 2.0f) * World::PART_SIZE,
                (y - World::WORLD_SIZE / 2.0f) * World::PART_SIZE, World::PART_SIZE, World::PART_SIZE);
}

void Exit::update(float delta) {}
