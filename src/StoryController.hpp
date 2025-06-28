// StoryController.hpp
#pragma once
#include "Character.hpp"
#include "Animator.hpp"
#include "Scene.hpp"
#include "UI.hpp"
#include "Sound.hpp"
#include "AutoMover.hpp"
#include <GLFW/glfw3.h>

enum StoryStep {
    INTRO,
    FIND_FLASHLIGHT,
    CHOICE,
    WALK_TO_PATH,
    PATH_END,
    RETURN,
    WALK_TO_FOREST,
    FOREST_SOUND,
    RETURN_AFTER_SCARED,
    WALK_TO_BALL,
    FOUND_BALL,
    FINISH
};

class StoryController {

private:
    GLFWwindow* window = nullptr;

public:
    StoryStep step = INTRO;
    float timer = 0.0f;

    void update(float dt, Character& player, AutoMover& mover, Animator& animator, UI& ui, SoundSystem& sound);
    void setWindow(GLFWwindow* win);
    bool isFlashLightOn() const;
};


