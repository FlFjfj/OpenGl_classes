//
// Created by opot on 01.04.18.
//

#include <GL/glew.h>

#include "MainMenu.h"
#include "ProgramBase.h"
#include "../GlUtils/SpriteBatch.h"
#include "../GlUtils/OrthographicCamera.h"
#include "../GlUtils/Texture.h"
#include "../GlUtils/Shader.h"

const int WORLD_WIDTH = 1920;
const int WORLD_HEIGHT = 1080;

namespace menu {
    GLFWwindow *window;

    fjfj::SpriteBatch *batch;
    fjfj::OrthographicCamera *cam;

    fjfj::Texture *tex;
    fjfj::Shader *shader;

    GLint proj_loc;
    GLint model_loc;
}

void MainMenu::init(GLFWwindow *win) {
    menu::window = win;

    menu::batch = new fjfj::SpriteBatch();
    menu::cam = new fjfj::OrthographicCamera(WORLD_WIDTH, WORLD_HEIGHT);

    menu::tex = new fjfj::Texture("texture/main_menu.png");
    menu::shader = new fjfj::Shader("shader/simple.vert", "shader/simple.frag");

    menu::model_loc = glGetUniformLocation(menu::shader->Program, "u_ModelTrans");
    menu::proj_loc = glGetUniformLocation(menu::shader->Program, "u_ProjTrans");
}

void MainMenu::update(float delta) {
    if (glfwGetKey(menu::window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        ProgramBase::changeState(ProgramBase::GAME);
    }

    menu::cam->update();
}

void MainMenu::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    menu::shader->Use();
    glUniformMatrix4fv(menu::proj_loc, 1, GL_FALSE, glm::value_ptr(menu::cam->proj));
    menu::batch->draw(*menu::tex, menu::model_loc, 0, 0, WORLD_WIDTH, WORLD_HEIGHT);
}