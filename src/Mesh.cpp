// Mesh.cpp
#include "Mesh.hpp"

Cube::Cube() {
    float vertices[] = {
        // positions           // normals         // texCoords

        // Front face
        -0.5f, -0.5f,  0.5f,   0, 0, 1,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   0, 0, 1,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   0, 0, 1,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   0, 0, 1,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0, 0, 1,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0, 0, 1,   0.0f, 0.0f,

        // Back face
        -0.5f, -0.5f, -0.5f,   0, 0, -1,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0, 0, -1,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0, 0, -1,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0, 0, -1,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0, 0, -1,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0, 0, -1,  1.0f, 0.0f,

        // Left face
        -0.5f,  0.5f,  0.5f,  -1, 0, 0,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  -1, 0, 0,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  -1, 0, 0,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  -1, 0, 0,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  -1, 0, 0,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  -1, 0, 0,   1.0f, 1.0f,

        // Right face
         0.5f,  0.5f,  0.5f,   1, 0, 0,   0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1, 0, 0,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1, 0, 0,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1, 0, 0,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1, 0, 0,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1, 0, 0,   0.0f, 0.0f,

         // Bottom face
         -0.5f, -0.5f, -0.5f,   0, -1, 0,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,   0, -1, 0,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,   0, -1, 0,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,   0, -1, 0,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,   0, -1, 0,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,   0, -1, 0,  0.0f, 1.0f,

         // Top face
         -0.5f,  0.5f, -0.5f,   0, 1, 0,   0.0f, 1.0f,
         -0.5f,  0.5f,  0.5f,   0, 1, 0,   0.0f, 0.0f,
          0.5f,  0.5f,  0.5f,   0, 1, 0,   1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,   0, 1, 0,   1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,   0, 1, 0,   1.0f, 1.0f,
         -0.5f,  0.5f, -0.5f,   0, 1, 0,   0.0f, 1.0f,
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coords attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


void Cube::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
