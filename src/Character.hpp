// Character.hpp
#pragma once
#include <glm/glm.hpp>
#include "Animator.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class Character {
public:
    glm::vec3 position; // Karakterin sahnedeki konumu
    glm::vec3 front;    // Karakterin bakt��� y�n (���k i�in kullan�l�r)
    glm::vec3 up;       // Yukar� y�n (sabit olarak genelde +Y)

    Cube body, leg;     // Geometrik par�alar: g�vde ve bacaklar

    Character();

    // Shader ile karakteri �izer, animator'dan animasyon verisi al�r
    void draw(const Shader& shader, const Animator& animator);
};
