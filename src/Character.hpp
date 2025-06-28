// Character.hpp
#pragma once
#include <glm/glm.hpp>
#include "Animator.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class Character {
public:
    glm::vec3 position; // Karakterin sahnedeki konumu
    glm::vec3 front;    // Karakterin baktýðý yön (ýþýk için kullanýlýr)
    glm::vec3 up;       // Yukarý yön (sabit olarak genelde +Y)

    Cube body, leg;     // Geometrik parçalar: gövde ve bacaklar

    Character();

    // Shader ile karakteri çizer, animator'dan animasyon verisi alýr
    void draw(const Shader& shader, const Animator& animator);
};
