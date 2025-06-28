#define GLM_ENABLE_EXPERIMENTAL
#include "AutoMover.hpp"

// AutoMover.cpp
#include <glm/gtx/norm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

void AutoMover::setTarget(const glm::vec3& position) {
    target = position;
    moving = true;
}

void AutoMover::update(float dt, Character& character) {
    if (!moving) return;

    glm::vec3 dir = target - character.position;
    float dist = glm::length(dir);

    if (dist < 0.05f) {
        moving = false;
        return;
    }

    glm::vec3 direction = glm::normalize(dir);
    character.position += direction * speed * dt;
    character.front = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
}

bool AutoMover::atTarget() const {
    return !moving;
}

bool AutoMover::isMoving() const {
    return moving;
}

bool AutoMover::isAtTarget(const glm::vec3& position , Character& character ) {
    return glm::distance(character.position, position) < 0.5f;
}

