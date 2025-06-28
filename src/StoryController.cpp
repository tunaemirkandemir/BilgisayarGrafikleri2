// StoryController.cpp
#include "StoryController.hpp"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


void StoryController::setWindow(GLFWwindow* win) {
	window = win;
}

bool StoryController::isFlashLightOn() const {
    return step >= CHOICE;
        //step == CHOICE || step == WALK_TO_PATH || step == PATH_END || step == RETURN || step == WALK_TO_FOREST || step == FOREST_SOUND || step == WALK_TO_BALL || step == FOUND_BALL || step == FINISH;
}


void StoryController::update(float dt, Character& player, AutoMover& mover, Animator& animator, UI& ui, SoundSystem& sound) {
    timer -= dt;
    bool asked = false;

    switch (step) {
    case INTRO:
        ui.showMessage("Cok karanlik... Fenerimi bulmaliyim. E'ye bas.", 5.0f);
        step = FIND_FLASHLIGHT;
        break;

    case FIND_FLASHLIGHT:
        // 'E' tusu ile main.cpp'de tetikleniyor
        break;

    case CHOICE:
        ui.showMessage("1 → Patikayi sec | 2 → Ormana gir", 0.0f); // Kullanici secene kadar goster
        break;

    case WALK_TO_PATH:
        if (mover.atTarget()) {
            step = PATH_END;
            ui.showMessage("Burada bir sey yokmus...", 3.0f);
            timer = 3.0f;
        }
        break;

    case PATH_END:
        if (timer <= 0.0f) {
            step = RETURN;
            mover.setTarget(glm::vec3(0.0f, 0.0f, 0.0f)); // Karakter geri donduruluyor
        }
        break;

    case RETURN:
        if (mover.atTarget()) {
            step = WALK_TO_FOREST;
            //mover.setTarget(glm::vec3(10.0f, 0.0f, -30.0f));
        }
        break;

    case WALK_TO_FOREST:
        mover.setTarget(glm::vec3(5.0f, 0.0f, -15.0f));

        if (mover.isAtTarget(glm::vec3(5.0f, 0.0f, -15.0f), player) && mover.scared == false && step != RETURN_AFTER_SCARED) {
            mover.scared = true;
            step = FOREST_SOUND;
            sound.playOnce("Assets/korku.wav");
			//sound.playLoop("Assets/orman_ambiyans.wav");
            ui.showMessage("Bir ses duydum...", 3.0f);
            timer = 1.0f;
        }
        break;

    case FOREST_SOUND:
        
        if (!asked) {
            ui.showMessage("Karanliktan bir ses geldi...\n1 → Devam Et | 2 → Geri Don", 3.0f);
            asked = true;
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            step = WALK_TO_BALL;
            mover.setTarget(glm::vec3(10.0f, 0.0f, -30.0f));
            ui.showMessage("Devam etmeye karar verdin.", 3.0f);
            asked = false;
        }
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            step = RETURN_AFTER_SCARED;
            mover.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
            ui.showMessage("Geri donmeye karar verdin.", 3.0f);
			asked = false;
        }
        break;

    case WALK_TO_BALL:
        if (mover.atTarget()) {
            step = FOUND_BALL;
            ui.showMessage("Topumu buldum!", 4.0f);
            sound.playOnce("Assets/sevincli.wav");
            timer = 4.0f;
        }
        break;

    case FOUND_BALL:
        if (timer <= 0.0f) {
            step = FINISH;
            ui.showMessage("Artik eve donebilirim.", 4.0f);
        }
        break;
     
    case RETURN_AFTER_SCARED:

        
        if (mover.isAtTarget(glm::vec3(0.0f, 0.0f, 0.0f), player) ) {
            ui.showMessage("Korkmamaliyim. Sadece hayali bir seydi....", 3.0f);
            mover.setTarget(glm::vec3(10.0f, 0.0f, -30.0f));
            
        }

        if (mover.isAtTarget(glm::vec3(10.0f, 0.0f, -30.0f), player)) {
            ui.showMessage("Topumu buldum!", 4.0f);
            sound.playOnce("Assets/sevincli.wav");
            timer = 4.0f;
            step = FOUND_BALL;

        }
        break;

    case FINISH:
        // Final sahnesi
        break;
    }
}


