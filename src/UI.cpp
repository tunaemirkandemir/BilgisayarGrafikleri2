// UI.cpp
#include "UI.hpp"
#include "stb_easy_font.h" // stb_easy_font k�t�phanesi i�in
#include <glad/glad.h>     // OpenGL fonksiyonlar� i�in
#include <iostream>        // Hata ay�klama ��kt�lar� i�in
#include <vector>          // Dinamik dizi (std::vector) i�in

// GLM k�t�phanesi, matris i�lemleri i�in
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Basit Vertex Shader Kayna��
// Bu shader, 2D pozisyon verilerini al�r ve bir projeksiyon matrisi ile d�n��t�r�r.
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos; // Vertex pozisyonu

uniform mat4 projection; // Projeksiyon matrisi

void main()
{
    gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
)";

// Basit Fragment Shader Kayna��
// Bu shader, t�m pikselleri beyaz renkte (RGB: 1.0, 1.0, 1.0) �izer.
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor; // ��k�� rengi

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); // Beyaz renk (RGBA)
}
)";

// UI s�n�f�n�n yap�c� (constructor) fonksiyonu
UI::UI() : currentText(""), timer(0.0f), active(false), shaderProgram(0), VAO(0), VBO(0) {

    shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // VAO'yu ba�la (t�m VBO ve �znitelik ayarlar� bu VAO'ya kaydedilir)
    glBindVertexArray(VAO);
    // VBO'yu ba�la (verileri VBO'ya y�kleyece�iz)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(0); // 0. konumdaki vertex attribute'u etkinle�tir

    // VBO ve VAO ba�lamalar�n� s�f�rla (iste�e ba�l�, iyi bir pratik)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// UI s�n�f�n�n y�k�c� (destructor) fonksiyonu
UI::~UI() {
    // OpenGL kaynaklar�n� serbest b�rak
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

// Mesaj� g�stermek i�in
void UI::showMessage(const std::string& text, float duration) {
    currentText = text;
    timer = duration;
    active = true;
}

// UI durumunu g�ncellemek i�in
void UI::update(float deltaTime) {
    if (active) {
        timer -= deltaTime;
        if (timer <= 0.0f) {
            active = false;
        }
    }
}

// UI elementlerini (metin) ekrana �izmek i�in
void UI::render(int screenWidth, int screenHeight) {
    if (!active) return; 
    float fontBuffer[99999]; // B�y�k bir tampon, yakla��k 6000 karakter kapasitesi

    // stb_easy_font_print, metni belirtilen konumda (10, screenHeight - 30) olu�turur.
    // ��kt�, fontBuffer'a yaz�l�r ve �retilen d�rtgen say�s� (num_quads) d�nd�r�l�r.
    int num_quads = stb_easy_font_print(10, screenHeight - 30, (char*)currentText.c_str(), NULL, fontBuffer, sizeof(fontBuffer));

    // Her d�rtgeni iki ��gene d�n��t�rmek i�in bir vekt�r olu�tur.
    // Her d�rtgen 2 ��gen ve her ��gen 3 k��e i�erir, yani 6 k��e.
    // Her k��e sadece 2 float (x,y) pozisyon verisi tutacak.
    std::vector<float> triangleVertices;
    triangleVertices.reserve(num_quads * 6 * 2); // Performans i�in yakla��k rezervasyon

    // stb_easy_font ��kt�s�n� al ve ��genlere d�n��t�r
    for (int i = 0; i < num_quads; ++i) {
        // Her d�rtgen (quad) 4 k��e i�erir: V0, V1, V2, V3
        // fontBuffer'daki format: (V0_x, V0_y, V0_s, V0_t), (V1_x, V1_y, V1_s, V1_t), ...
        // Her k��e 4 float (16 byte) yer kaplar.

        // Mevcut d�rtgenin fontBuffer i�indeki ba�lang�� indeksi (float cinsinden)
        int quad_start_idx = i * 4 * 4; // i. d�rtgen * 4 k��e/d�rtgen * 4 float/k��e

        // D�rtgenin k��e pozisyonlar�n� al (sadece x,y koordinatlar�n� al�yoruz)
        float v0x = fontBuffer[quad_start_idx + 0];
        float v0y = fontBuffer[quad_start_idx + 1];

        float v1x = fontBuffer[quad_start_idx + 4];
        float v1y = fontBuffer[quad_start_idx + 5];

        float v2x = fontBuffer[quad_start_idx + 8];
        float v2y = fontBuffer[quad_start_idx + 9];

        float v3x = fontBuffer[quad_start_idx + 12];
        float v3y = fontBuffer[quad_start_idx + 13];

        // Birinci ��geni olu�tur: V0, V1, V2
        triangleVertices.push_back(v0x); triangleVertices.push_back(v0y);
        triangleVertices.push_back(v1x); triangleVertices.push_back(v1y);
        triangleVertices.push_back(v2x); triangleVertices.push_back(v2y);

        // �kinci ��geni olu�tur: V0, V2, V3
        triangleVertices.push_back(v0x); triangleVertices.push_back(v0y);
        triangleVertices.push_back(v2x); triangleVertices.push_back(v2y);
        triangleVertices.push_back(v3x); triangleVertices.push_back(v3y);
    }

    // Modern OpenGL ayarlar�
    glDisable(GL_DEPTH_TEST); // Metnin di�er objelerin �n�nde g�r�nmesini sa�la
    // glDisable(GL_LIGHTING); // Modern OpenGL'de sabit ayd�nlatma boru hatt� yoktur

    // Shader program�n� etkinle�tir
    glUseProgram(shaderProgram);

    // Ekran boyutlar�na g�re ortografik projeksiyon matrisi olu�tur
    // Bu, 2D UI elemanlar�n� ekran koordinatlar�nda do�ru �ekilde konumland�rmay� sa�lar.
    //glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
    glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f);

    // Projeksiyon matrisini shader'daki "projection" uniform de�i�kenine g�nder
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // ��genlenmi� vertex verilerini VBO'ya y�kle
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, triangleVertices.size() * sizeof(float), triangleVertices.data(), GL_STREAM_DRAW);

    // VAO'yu ba�la (�nceden tan�mlanm�� �znitelik ayarlar� yeniden uygulan�r)
    glBindVertexArray(VAO);

    // OpenGL'e ��genleri �izmesini s�yle
    // Toplam k��e say�s�: num_quads (d�rtgen) * 2 (��gen/d�rtgen) * 3 (k��e/��gen) = num_quads * 6
    glDrawArrays(GL_TRIANGLES, 0, num_quads * 6);
    glBindVertexArray(0); // VAO ba�lamas�n� s�f�rla

    glUseProgram(0); // Shader program�n� devre d��� b�rak

    glEnable(GL_DEPTH_TEST); // Derinlik testini tekrar etkinle�tir
}

// ---
// ### Yard�mc� Fonksiyonlar

// Shader'� derlemek i�in yard�mc� fonksiyon
unsigned int UI::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type); // Shader nesnesi olu�tur
    const char* src = source.c_str();      // Kaynak kodu i�aret�isi
    glShaderSource(id, 1, &src, nullptr);   // Shader kayna��n� ata
    glCompileShader(id);                    // Shader'� derle

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); // Derleme durumunu sorgula
    if (result == GL_FALSE) { // E�er derleme ba�ar�s�zsa
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); // Hata mesaj� uzunlu�unu al
        char* message = (char*)alloca(length * sizeof(char)); // Mesaj i�in bellek ay�r
        glGetShaderInfoLog(id, length, &length, message);     // Hata mesaj�n� al
        // Hata mesaj�n� konsola yazd�r
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(id); // Shader'� sil
        return 0;           // 0 d�nd�r (hata kodu)
    }
    return id; // Derlenmi� shader ID'sini d�nd�r
}

// Shader program�n� olu�turmak i�in yard�mc� fonksiyon
unsigned int UI::createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    unsigned int program = glCreateProgram(); // Yeni bir shader program� olu�tur
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);   // Vertex shader'� derle
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource); // Fragment shader'� derle

    glAttachShader(program, vs); // Vertex shader'� programa ekle
    glAttachShader(program, fs); // Fragment shader'� programa ekle
    glLinkProgram(program);      // Program� ba�la
    glValidateProgram(program);  // Program� do�rula (hata ay�klama i�in faydal�)

    glDeleteShader(vs); // Shaderlar� programa ba�lad�ktan sonra silebiliriz
    glDeleteShader(fs); // Bellek bo�altma

    return program; // Shader program�n�n ID'sini d�nd�r
}

