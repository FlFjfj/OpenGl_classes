//
// Created by opot on 01.04.18.
//

#include <GL/glew.h>

#include "GameOver.h"
#include "ProgramBase.h"
#include "../GlUtils/SpriteBatch.h"
#include "../GlUtils/OrthographicCamera.h"
#include "../GlUtils/Texture.h"
#include "../GlUtils/Shader.h"
#include "../GlUtils/BitmapFont.h"
#include "MainGame.h"

GLFWwindow *window;

const int WORLD_WIDTH = 1920;
const int WORLD_HEIGHT = 1080;

fjfj::SpriteBatch *batch;
fjfj::OrthographicCamera *cam;

fjfj::Texture *tex;
fjfj::Shader *shader;
fjfj::BitmapFont *font;

GLint proj_loc;
GLint model_loc;

float score;

void fjfj::GameOver::init(GLFWwindow *win) {
    window = win;

    batch = new fjfj::SpriteBatch();
    cam = new fjfj::OrthographicCamera(WORLD_WIDTH, WORLD_HEIGHT);

    tex = new fjfj::Texture("texture/gameover.png");
    shader = new fjfj::Shader("shader/simple.vert", "shader/simple.frag");

    model_loc = glGetUniformLocation(shader->Program, "u_ModelTrans");
    proj_loc = glGetUniformLocation(shader->Program, "u_ProjTrans");

    font = new BitmapFont("0123456789.", new Texture("texture/font.png"));
}

void fjfj::GameOver::update(float delta) {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        ProgramBase::changeState(ProgramBase::MENU);
        MainGame::restart();
    }

    cam->update();
}

void fjfj::GameOver::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    shader->Use();
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(cam->proj));
    batch->draw(*tex, model_loc, 0, 0, WORLD_WIDTH, WORLD_HEIGHT);

    font->draw(batch, cam, std::to_string(score), 70, -170, 100, 100);
}

void fjfj::GameOver::setScore(float time) {
    score = time;
}
