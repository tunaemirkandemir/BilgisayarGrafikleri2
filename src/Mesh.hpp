// Mesh.hpp
#pragma once
#include <glad/glad.h>

class Cube {
public:
    unsigned int VAO, VBO;

    Cube();         // VAO ve VBO oluþturur, vertex verilerini gönderir
    void draw() const; // Þekli çizer
};
