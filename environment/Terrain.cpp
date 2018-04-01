//
// Created by opot on 01.04.18.
//

#include "Terrain.h"

StaticObject::StaticObject(Texture *tex) : tex(tex) {}

Terrain::Terrain(Texture *tex) : StaticObject(tex) {}

void Terrain::draw(int x, int y) {}

void Terrain::update(float delta) {}

Exit::Exit(Texture *tex) : StaticObject(tex) {}

void Exit::draw(int x, int y) {}

void Exit::update(float delta) {}
