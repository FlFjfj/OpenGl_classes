//
// Created by opot on 01.04.18.
//

#include "ProgramBase.h"

#include "MainGame.h"
#include "MainMenu.h"
#include "GameOver.h"

ProgramBase::GameState state = ProgramBase::MENU;

void ProgramBase::init(GLFWwindow *window) {
    fjfj::MainGame::init(window);
    MainMenu::init(window);
    fjfj::GameOver::init(window);
}

void ProgramBase::update(float delta) {
    switch (state) {
        case GAME:
            fjfj::MainGame::update(delta);
            return;
        case MENU:
            MainMenu::update(delta);
            return;
        case DEAD:
            fjfj::GameOver::update(delta);
            return;
        default:
            return;
    }
}

void ProgramBase::render() {
    switch (state) {
        case GAME:
            fjfj::MainGame::render();
            return;
        case MENU:
            MainMenu::render();
            return;
        case DEAD:
            fjfj::GameOver::render();
            return;
        default:
            return;
    }
}

void ProgramBase::changeState(ProgramBase::GameState s) {
    state = s;
}
