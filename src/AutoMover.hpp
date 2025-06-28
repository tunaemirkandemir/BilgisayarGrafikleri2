
#pragma once
#include <glm/glm.hpp>
#include "Character.hpp"

class AutoMover {
    glm::vec3 target;
    bool moving = false;
    float speed = 3.0f;
    

public:
    bool scared = false;
    void setTarget(const glm::vec3& position);
    void update(float dt, Character& character);
    bool isAtTarget(const glm::vec3& position , Character& character);
    bool atTarget() const;
    bool isMoving() const;
};
