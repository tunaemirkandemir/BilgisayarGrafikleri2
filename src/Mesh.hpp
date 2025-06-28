// Mesh.hpp
#pragma once
#include <glad/glad.h>

class Cube {
public:
    unsigned int VAO, VBO;

    Cube();         // VAO ve VBO olu�turur, vertex verilerini g�nderir
    void draw() const; // �ekli �izer
};
