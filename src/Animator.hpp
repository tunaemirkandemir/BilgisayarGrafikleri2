// Animator.hpp
#pragma once

class Animator {
    float legAngle = 0.0f;
    float speed = 180.0f;  // Derece/saniye
    bool flip = false;

public:
    void update(float dt, bool walking);
    float getLegAngle() const;
};


//#pragma once
//
//class Animator {
//private:
//    bool walking = false;
//    float time = 0.0f;
//
//public:
//    void start();                // yürüyüþ baþlat
//    void stop();                 // yürüyüþ durdur
//    void update(float deltaTime);  // zaman güncelle
//    float getLegAngle() const;     // bacak açýsý (animasyon)
//};
