// main.cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Shader.hpp"
#include "Character.hpp"
#include "Scene.hpp"
#include "Animator.hpp"
#include "UI.hpp"
#include "AutoMover.hpp"
#include "Sound.hpp"
#include "StoryController.hpp"

int screenWidth = 800;
int screenHeight = 600;

GLFWwindow* window;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}




bool initGLFW() {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, "Modern OpenGL Scene", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return true;
}

bool initGLAD() {
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

glm::vec3 freeCamPos = glm::vec3(0.0f, 2.0f, 5.0f);
glm::vec3 freeCamFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 freeCamUp = glm::vec3(0.0f, 1.0f, 0.0f);


float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400.0f, lastY = 300.0f; // ekran ortasý
bool firstMouse = true;
//Kamera modu baþlýk alanlarý
enum class CameraMode {
    firstPerson,
    thirdPerson,
    Overhead,
    Stable,
    FreeCamera
};

CameraMode cameraMode = CameraMode::thirdPerson; //baþlangýçta kamera modu thirdPerson olacak.

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (cameraMode != CameraMode::FreeCamera)
        return;

    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)(xpos - lastX);
    float yoffset = (float)(lastY - ypos);
    lastX = (float)xpos;
    lastY = (float)ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    freeCamFront = glm::normalize(direction);
};


int main() {

    if (!initGLFW() || !initGLAD()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    

    Character player;
    Scene scene;
    Animator animator;
    AutoMover mover;
    SoundSystem sound;
    UI ui;
    StoryController story;
    story.setWindow(window);


 
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader shader =  Shader("shaders/spotlight.vert", "shaders/spotlight.frag");

    //sound.playLoop("Assets/orman_ambiyans.wav");

    float lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        //sound.playLoop("Assets/orman_ambiyans.wav");
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && story.step == CHOICE) {
            story.step = WALK_TO_PATH;
            mover.setTarget(glm::vec3(-7.5f, 0.0f, -40.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && story.step == CHOICE) {
            story.step = WALK_TO_FOREST;
            mover.setTarget(glm::vec3(5.0f, 0.0f, -15.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && story.step == FIND_FLASHLIGHT) {

           sound.playOnce("Assets/fener.wav");
		   sound.stop();

            ui.showMessage("Yolu gormeye basladim.", 3.0f);
            story.step = CHOICE;
        }
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}   
       
        //cameraMode deðiþtirme
        bool cameraKeyPressed = false;
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !cameraKeyPressed) {
            cameraKeyPressed = true;
            cameraMode = static_cast<CameraMode>((static_cast<int>(cameraMode) + 1) % 5);

            if (cameraMode == CameraMode::FreeCamera) {
                firstMouse = true; // fare sýçramasýný engelle
            }
            
            // while sürekli deðiþmesin diye delay ekledim
            int delay = 1000000000;
            while (delay > 0) {
                delay--;
            }

        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            cameraKeyPressed = false;
        }


		// WASD Modunda hareket
        if (cameraMode == CameraMode::FreeCamera) {
            float cameraSpeed = 5.0f * deltaTime;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                freeCamPos += cameraSpeed * freeCamFront;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                freeCamPos -= cameraSpeed * freeCamFront;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                freeCamPos -= glm::normalize(glm::cross(freeCamFront, freeCamUp)) * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                freeCamPos += glm::normalize(glm::cross(freeCamFront, freeCamUp)) * cameraSpeed;
        }

       
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);
        glm::mat4 view;
        switch (cameraMode)
        {
        case CameraMode::firstPerson:

            view = glm::lookAt(
                player.position + glm::vec3(0.0f, 1.6f, 0.0f), // kafa hizasý
                player.position + glm::vec3(0.0f, 1.6f, 0.0f) + player.front,
                glm::vec3(0.0f, 1.0f, 0.0f)
            );

            break;
        case CameraMode::thirdPerson:
            glm::vec3 behind = -glm::normalize(player.front); // karakterin arka yönü
            glm::vec3 cameraOffset = behind * 5.0f + glm::vec3(0.0f, 2.0f, 0.0f); // yükseklik + mesafe


                view = glm::lookAt(
                   /* player.position + glm::vec3(0.0f, 2.0f, 5.0f),*/
                    player.position + cameraOffset,
                    player.position + glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f)
                );

            break;
        case CameraMode::Overhead:

            view = glm::lookAt(
            player.position + glm::vec3(0.0f, 10.0f, 0.1f),
            player.position,
            glm::vec3(0.0f, 0.0f, -1.0f) // yukarýdan bakarken up vektörü öne doðru olmalý
        );

            break;
		case CameraMode::Stable:    
			// Sabit kamera modu, karakterin konumuna göre sabit bir bakýþ açýsý
			view = glm::lookAt(
				glm::vec3(0.0f, 10.0f, 10.0f), // sabit kamera konumu
				glm::vec3(0.0f, 0.0f, 0.0f),   // bakýlan nokta
				glm::vec3(0.0f, 1.0f, 0.0f)    // yukarý yön
			);
			break;
		case CameraMode::FreeCamera:
            view = glm::lookAt(freeCamPos, freeCamPos + freeCamFront, freeCamUp);
			break;
        default:
            break;
        }

        shader.setMat4("projection", &projection[0][0]);
        shader.setMat4("view", &view[0][0]);

        glm::vec3 lightPos = player.position + glm::vec3(0.0f, 1.5f, 0.0f);
        glm::vec3 lightDir = player.front;
        shader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);
        shader.setVec3("lightDir", lightDir.x, lightDir.y, lightDir.z);
        shader.setFloat("cutOff", glm::cos(glm::radians(20.0f)));

		shader.setInt("texture1", 0); // texture1 is bound to GL_TEXTURE0

		
        shader.setBool("spotlightEnabled", story.isFlashLightOn());

        shader.setVec3("lightColor", 1.0f, 1.0f, 0.8f);
        glm::vec3 cameraPosition = player.position + glm::vec3(0.0f, 2.0f, 5.0f); // third-person
        shader.setVec3("viewPos", cameraPosition.x, cameraPosition.y, cameraPosition.z);



        mover.update(deltaTime, player);
        animator.update(deltaTime, mover.isMoving());
        story.update(deltaTime, player, mover, animator, ui, sound);
        ui.update(deltaTime);

        scene.draw(shader);
        player.draw(shader, animator);
        ui.render(screenWidth, screenHeight);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}




