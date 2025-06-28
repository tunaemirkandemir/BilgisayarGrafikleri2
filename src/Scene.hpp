// Scene.hpp
#pragma once
#include <glm/glm.hpp>
#include "Shader.hpp"
#include "Mesh.hpp"
#include <vector>

class Scene {
private:
    std::vector<glm::vec3> treePositions;
    std::vector<float> treeScales;
	unsigned int groundTexture; // Zemin dokusu

    void generateTrees();



public:
    glm::vec3 ballPosition;  // Topun pozisyonu
    bool ballVisible = true; // Top sahnede g�r�n�yor mu?

    Cube ground;      // Zemin
    Cube path;        // Yol (patika)
    Cube treeTrunk;   // A�a� g�vdesi
    Cube treeLeaves;  // A�a� yapraklar�

    Scene();

    // Shader kullanarak sahneyi �izer
    void draw(const Shader& shader);
};

