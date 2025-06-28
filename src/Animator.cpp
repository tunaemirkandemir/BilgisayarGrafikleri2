// Animator.cpp
#include "Animator.hpp"

void Animator::update(float dt, bool walking) {
    if (walking) {
        legAngle += (flip ? -1 : 1) * speed * dt;
        if (legAngle > 30.0f) {
            legAngle = 30.0f;
            flip = true;
        }
        else if (legAngle < -30.0f) {
            legAngle = -30.0f;
            flip = false;
        }
    }
    else {
        if (legAngle > 0.1f) {
            legAngle -= speed * dt;
        }
        else if (legAngle < -0.1f) {
            legAngle += speed * dt;
        }
        else {
            legAngle = 0.0f;
        }
    }
}

float Animator::getLegAngle() const {
    return legAngle;
}
