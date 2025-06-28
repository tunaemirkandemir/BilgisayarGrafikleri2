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
//    void start();                // y�r�y�� ba�lat
//    void stop();                 // y�r�y�� durdur
//    void update(float deltaTime);  // zaman g�ncelle
//    float getLegAngle() const;     // bacak a��s� (animasyon)
//};
