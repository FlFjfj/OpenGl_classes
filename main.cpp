#include "GlUtils/Engine.h"
#include "GameState/ProgramBase.h"

int main(int argc, char** argv) {

    fjfj::Engine e(ProgramBase::init, ProgramBase::update, ProgramBase::render);
    e.start();

    return 0;
}