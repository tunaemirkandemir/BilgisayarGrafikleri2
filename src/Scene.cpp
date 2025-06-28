#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Scene.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Texture.hpp"


Scene::Scene() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Tohum
    generateTrees();
    ballPosition = glm::vec3(10.0f, 0.25f, -30.0f);
    groundTexture = LoadTexture("C:/Users/90535/source/repos/BlgisayarGrafikleriProje2/Assets/grass.jpg", true);
}

void Scene::generateTrees() {
    treePositions.clear();
    treeScales.clear();

    int treeCount = 500;

    for (int i = 0; i < treeCount; ++i) {
        float x = static_cast<float>(std::rand() % 120 - 60); 
        float z = static_cast<float>(std::rand() % 120 - 60); 

        // Patika hattını boş bırak (örneğin x ≈ -5 ile 5 ve z > -25 için)
        if (std::abs(x) < 6.0f && z > 17.0f) continue;

        // Pozisyon ve ölçek ekle
        treePositions.emplace_back(x, 0.0f, z);
        float scale = 1.2f + static_cast<float>(std::rand() % 40) / 100.0f; // 0.8 - 1.2
        treeScales.push_back(scale);
    }
}

void Scene::draw(const Shader& shader) {
    glm::mat4 model;

    // Ground
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    shader.setInt("texture1", 0);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.05f, -10.0f));
    model = glm::scale(model, glm::vec3(1000.0f, 0.1f, 1000.0f));
    shader.setMat4("model", &model[0][0]);
    shader.setVec3("objectColor", 0.1f, 0.4f, 0.1f);
	
    ground.draw();

    // Left Path
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-7.5f, 0.0f, -20.0f));
    model = glm::scale(model, glm::vec3(4.0f, 0.1f, 40.0f));
    shader.setMat4("model", &model[0][0]);
    shader.setVec3("objectColor", 0.5f, 0.3f, 0.1f);
    path.draw();

    // Right Path
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(7.5f, 0.0f, -20.0f));
    model = glm::scale(model, glm::vec3(3.0f, 0.1f, 100.0f));
    shader.setMat4("model", &model[0][0]);
    shader.setVec3("objectColor", 0.3f, 0.6f, 0.3f);
    path.draw();

    for (size_t i = 0; i < treePositions.size(); ++i) {
        glm::vec3 pos = treePositions[i];
        float scale = treeScales[i];

        // Trunk
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos + glm::vec3(0.0f, 1.0f * scale, 0.0f));
        model = glm::scale(model, glm::vec3(0.3f, 2.0f, 0.3f) * scale);
        shader.setMat4("model", &model[0][0]);
        shader.setVec3("objectColor", 0.36f, 0.18f, 0.05f);
        treeTrunk.draw();

        // Leaves
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos + glm::vec3(0.0f, 2.5f * scale, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f) * scale);
        shader.setMat4("model", &model[0][0]);
        shader.setVec3("objectColor", 0.0f, 0.5f, 0.0f);
        treeLeaves.draw();
    }


    if (ballVisible) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, ballPosition);
        model = glm::scale(model, glm::vec3(0.25f));
        shader.setMat4("model", &model[0][0]);
        shader.setVec3("objectColor", 1.0f, 0.0f, 0.0f);
        ground.draw();
    }
}

