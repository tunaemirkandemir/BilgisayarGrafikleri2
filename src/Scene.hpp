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
    bool ballVisible = true; // Top sahnede görünüyor mu?

    Cube ground;      // Zemin
    Cube path;        // Yol (patika)
    Cube treeTrunk;   // Aðaç gövdesi
    Cube treeLeaves;  // Aðaç yapraklarý

    Scene();

    // Shader kullanarak sahneyi çizer
    void draw(const Shader& shader);
};

