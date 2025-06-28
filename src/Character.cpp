// Character.cpp
#include "Character.hpp"
#include <glm/gtc/matrix_transform.hpp>

Character::Character() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Character::draw(const Shader& shader, const Animator& animator) {
    float legAngle = animator.getLegAngle();

    // Gövde
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position + glm::vec3(0.0f, 0.8f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.6f, 0.3f));
    shader.setMat4("model", &model[0][0]);
    shader.setVec3("objectColor", 1.0f, 0.0f, 0.0f);
    body.draw();

    // Sol bacak
    model = glm::mat4(1.0f);
    model = glm::translate(model, position + glm::vec3(-0.15f, 0.25f, 0.0f));
    model = glm::rotate(model, glm::radians(legAngle), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.5f, 0.2f));
    shader.setMat4("model", &model[0][0]);
    shader.setVec3("objectColor", 0.6f, 0.3f, 0.1f);
    leg.draw();

    // Sað bacak
    model = glm::mat4(1.0f);
    model = glm::translate(model, position + glm::vec3(0.15f, 0.25f, 0.0f));
    model = glm::rotate(model, glm::radians(-legAngle), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.5f, 0.2f));
    shader.setMat4("model", &model[0][0]);
    shader.setVec3("objectColor", 0.6f, 0.3f, 0.1f);
    leg.draw();

    // Kafa (yerine küçük bir küp)
    model = glm::mat4(1.0f);
    model = glm::translate(model, position + glm::vec3(0.0f, 1.3f, 0.0f));
    model = glm::scale(model, glm::vec3(0.25f));
    shader.setMat4("model", &model[0][0]);
    shader.setVec3("objectColor", 1.0f, 0.8f, 0.6f);
    body.draw();
}


