//
// Created by opot on 06.04.17.
//

#include <GL/glew.h>
#include <iostream>
#include <ctime>
#include <random>

#include "MainGame.h"
#include "../GlUtils/OrthographicCamera.h"
#include "../GlUtils/Shader.h"
#include "../GlUtils/SpriteBatch.h"
#include "../World.h"
#include "../player/Player.h"
#include "../GlUtils/BitmapFont.h"
#include "../environment/Lizard.h"
#include "../environment/Tail.h"

namespace fjfj {

SpriteBatch *batch;
OrthographicCamera *cam;

World *world;
Player *player;
BitmapFont *font;

float elapsed = 0;
float delay = 0;

const int WORLD_WIDTH = 1280;
const int WORLD_HEIGHT = 720;

GLFWwindow *win;

std::mt19937 gen(unsigned(std::time(0)));
std::uniform_real_distribution<> dist(0, 1);

GLuint fbo;
Shader *post;
GLint model_loc;
GLint time_loc;
Texture *fbo_tex;

double genNumber() {
  return dist(gen);
}

void MainGame::init(GLFWwindow *window) {
  glEnable(GL_MULTISAMPLE);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  fbo_tex = new Texture();

  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glGenTextures(1, &fbo_tex->texture);
  glBindTexture(GL_TEXTURE_2D, fbo_tex->texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WORLD_WIDTH, WORLD_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_tex->texture, 0);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  post = new Shader("shader/post.vert", "shader/post.frag");
  model_loc = glGetUniformLocation(post->Program, "u_ModelTrans");
  time_loc = glGetUniformLocation(post->Program, "u_Time");

  batch = new SpriteBatch();
  cam = new OrthographicCamera(WORLD_WIDTH, WORLD_HEIGHT);

  world = new World(batch, cam, nullptr);
  Tail::shader = new Shader("shader/light.vert", "shader/light.frag");
  Tail::texture = new Texture("texture/tail.png");
  glfwSetMouseButtonCallback(window, PlayerController::mouseClickHandler);
  player = new Player(new PlayerController(window), batch, cam, &world->map);
  font = new BitmapFont("0123456789.", new Texture("texture/font.png"));

  Lizard::base = new Texture("texture/lizard.png");
  Lizard::tail = new Texture("texture/tail.png");
  Lizard::slice = new Texture("texture/tailshot.png");

  Lizard::shader = new Shader("shader/lizard.vert", "shader/lizard.frag");

  Lizard::u_ModelTrans = glGetUniformLocation(Lizard::shader->Program, "u_ModelTrans");
  Lizard::u_ProjTrans = glGetUniformLocation(Lizard::shader->Program, "u_ProjTrans");
  Lizard::u_FrameCount = glGetUniformLocation(Lizard::shader->Program, "u_FrameCount");
  Lizard::u_FrameTime = glGetUniformLocation(Lizard::shader->Program, "u_FrameTime");
  Lizard::u_Time = glGetUniformLocation(Lizard::shader->Program, "u_Time");

  win = window;
}

void MainGame::update(float delta) {
  elapsed += delta;

  delay -= delta;
  if (delay <= 0) {
    delay += genNumber() * 30;
    float world_size = World::WORLD_SIZE * World::PART_SIZE;
    float x = (genNumber() - 0.5f) * (world_size - 200);
    float y = (genNumber() - 0.5f) * (world_size - 200);
    world->map.push_back(new Lizard({ x, y }, player, &world->map));
  }

  world->update(delta);
  player->update(delta, elapsed);

  cam->update();
}

void MainGame::render() {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  world->render(batch, cam, elapsed);
  player->render(elapsed);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  post->Use();
  glUniform1f(time_loc, elapsed);
  batch->draw(*fbo_tex, model_loc, 0, 0, 2, 2);
  glUseProgram(0);

  font->draw(batch, cam, std::to_string(elapsed), -WORLD_WIDTH / 2 + 25, WORLD_HEIGHT / 2 - 25, 40, 40);
}

void MainGame::restart() {
  elapsed = 0;
  delete (world);
  delete (player);
  delete (font);
  delete (batch);
  delete (cam);

  glDeleteFramebuffers(1, &fbo);

  MainGame::init(win);
}

}
