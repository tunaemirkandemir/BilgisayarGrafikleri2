
// UI.hpp (�rnek - Shader program ID'si ve GLM k�t�phanesi i�in include'lar eklenecek)
#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class UI {
public:
    UI();
    ~UI();

    void showMessage(const std::string& text, float duration);
    void update(float deltaTime);
    void render(int screenWidth, int screenHeight);

    // Shader program ID'si
    unsigned int shaderProgram;
    // VAO ve VBO ID'leri
    unsigned int VAO, VBO;

private:
    std::string currentText;
    float timer;
    bool active;

    // Shaderlar� y�klemek ve derlemek i�in yard�mc� fonksiyonlar
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
};

#endif // UI_HPP



/////////////////////////////////////////////////////////
//// UI.hpp
//#pragma once
//#include <string>
//
//class UI {
//private:
//    std::string currentText;
//    float timer = 0.0f;
//    bool active = false;
//
//public:
//    // Mesaj g�ster: belirli s�re boyunca
//    void showMessage(const std::string& text, float duration);
//
//    // S�reyi azalt, mesaj� kapat
//    void update(float deltaTime);
//
//    // Ekrana yaz�y� �iz
//    void render(int screenWidth, int screenHeight);
//
//    // �u anda yaz� aktif mi?
//    bool isActive() const { return active; }
//};
/////////////////////////////////////////////////////////

//#pragma once
//#include <string>
//
//class UI {
//private:
//    std::string currentText;
//    float timer = 0.0f;
//    bool active = false;
//
//public:
//    void showMessage(const std::string& text, float duration);
//    void update(float deltaTime);
//    void render(int screenWidth, int screenHeight);
//    bool isActive() const;
//};
