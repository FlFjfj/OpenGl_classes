//
// Created by opot on 20.04.17.
//

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SpriteBatch.h"

namespace fjfj {

    SpriteBatch::SpriteBatch() {
        GLfloat vert[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        };

        this->square = new Mesh(vert, 6);
    }

    void SpriteBatch::draw(const Texture &tex, GLint model_location, float x, float y, float width, float height) {

        glBindTexture(GL_TEXTURE_2D, tex.texture);
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(
                glm::scale(glm::translate(glm::mat4(), glm::vec3(x, y, 0)), glm::vec3(width, height, 1))));

        this->square->draw();
        glBindTexture(GL_TEXTURE_2D, 0);

    }

    void SpriteBatch::draw(const Texture &tex, GLint model_location, float x, float y, float width, float height, float angle) {

        glBindTexture(GL_TEXTURE_2D, tex.texture);
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(
                glm::rotate(glm::scale(glm::translate(glm::mat4(), glm::vec3(x, y, 0)), glm::vec3(width, height, 1)), angle, glm::vec3(0,0,1))));

        this->square->draw();
        glBindTexture(GL_TEXTURE_2D, 0);

    }
}