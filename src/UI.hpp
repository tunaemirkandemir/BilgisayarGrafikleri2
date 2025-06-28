
// UI.hpp (Örnek - Shader program ID'si ve GLM kütüphanesi için include'lar eklenecek)
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

    // Shaderlarý yüklemek ve derlemek için yardýmcý fonksiyonlar
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
//    // Mesaj göster: belirli süre boyunca
//    void showMessage(const std::string& text, float duration);
//
//    // Süreyi azalt, mesajý kapat
//    void update(float deltaTime);
//
//    // Ekrana yazýyý çiz
//    void render(int screenWidth, int screenHeight);
//
//    // Þu anda yazý aktif mi?
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
