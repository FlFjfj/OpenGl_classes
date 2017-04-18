//
// Created by opot on 06.04.17.
//

#include <iostream>
#include "Model.h"

namespace fjfj {

    Model::Model(GLfloat vertices[], int vert_count) {
        this->vert_count = vert_count;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (sizeof(GLfloat) * 5 * vert_count), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    Model::~Model() {
        //glDeleteBuffers(1, &VBO);
        //glDeleteVertexArrays(1, &VAO);
    }

    void Model::draw() {
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, this->vert_count);
        glBindVertexArray(0);
    }

    Model* Model::genCube() {
        GLfloat cube_vert[] = {
                -0.5f, -0.5f, -0.5f, 0.33f, 0.5f,//FRONT
                0.5f, -0.5f, -0.5f, 0.66f, 0.5f,
                0.5f, 0.5f, -0.5f, 0.66f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.33f, 0.5f,
                -0.5f, 0.5f, -0.5f, 0.33f, 0.0f,
                0.5f, 0.5f, -0.5f, 0.66f, 0.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.5f,//BACK
                0.5f, -0.5f, 0.5f, 0.33f, 0.5f,
                0.5f, 0.5f, 0.5f, 0.33f, 0.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.5f,
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 0.33f, 0.0f,

                -0.5f, 0.5f, -0.5f, 0.66f, 0.5f,//TOP
                0.5f, 0.5f, -0.5f, 1.0f, 0.5f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, 0.5f, -0.5f, 0.66f, 0.5f,
                -0.5f, 0.5f, 0.5f, 0.66f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,//BOTTOM
                0.5f, -0.5f, -0.5f, 0.33f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.33f, 0.5f,

                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.5f,
                0.5f, -0.5f, 0.5f, 0.33f, 0.5f,

                -0.5f, -0.5f, -0.5f, 0.33f, 1.0f,//LEFT
                -0.5f, 0.5f, -0.5f, 0.66f, 1.0f,
                -0.5f, 0.5f, 0.5f, 0.66f, 0.5f,

                -0.5f, -0.5f, -0.5f, 0.33f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.33f, 0.5f,
                -0.5f, 0.5f, 0.5f, 0.66f, 0.5f,

                0.5f, -0.5f, -0.5f, 0.66f, 1.0f,//RIGHT
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.5f,

                0.5f, -0.5f, -0.5f, 0.66f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.66f, 0.5f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.5f
        };

        return new Model(cube_vert, 36);

    }

}