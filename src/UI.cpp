// UI.cpp
#include "UI.hpp"
#include "stb_easy_font.h" // stb_easy_font kütüphanesi için
#include <glad/glad.h>     // OpenGL fonksiyonlarý için
#include <iostream>        // Hata ayýklama çýktýlarý için
#include <vector>          // Dinamik dizi (std::vector) için

// GLM kütüphanesi, matris iþlemleri için
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Basit Vertex Shader Kaynaðý
// Bu shader, 2D pozisyon verilerini alýr ve bir projeksiyon matrisi ile dönüþtürür.
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos; // Vertex pozisyonu

uniform mat4 projection; // Projeksiyon matrisi

void main()
{
    gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
}
)";

// Basit Fragment Shader Kaynaðý
// Bu shader, tüm pikselleri beyaz renkte (RGB: 1.0, 1.0, 1.0) çizer.
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor; // Çýkýþ rengi

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); // Beyaz renk (RGBA)
}
)";

// UI sýnýfýnýn yapýcý (constructor) fonksiyonu
UI::UI() : currentText(""), timer(0.0f), active(false), shaderProgram(0), VAO(0), VBO(0) {

    shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // VAO'yu baðla (tüm VBO ve öznitelik ayarlarý bu VAO'ya kaydedilir)
    glBindVertexArray(VAO);
    // VBO'yu baðla (verileri VBO'ya yükleyeceðiz)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(0); // 0. konumdaki vertex attribute'u etkinleþtir

    // VBO ve VAO baðlamalarýný sýfýrla (isteðe baðlý, iyi bir pratik)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// UI sýnýfýnýn yýkýcý (destructor) fonksiyonu
UI::~UI() {
    // OpenGL kaynaklarýný serbest býrak
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

// Mesajý göstermek için
void UI::showMessage(const std::string& text, float duration) {
    currentText = text;
    timer = duration;
    active = true;
}

// UI durumunu güncellemek için
void UI::update(float deltaTime) {
    if (active) {
        timer -= deltaTime;
        if (timer <= 0.0f) {
            active = false;
        }
    }
}

// UI elementlerini (metin) ekrana çizmek için
void UI::render(int screenWidth, int screenHeight) {
    if (!active) return; 
    float fontBuffer[99999]; // Büyük bir tampon, yaklaþýk 6000 karakter kapasitesi

    // stb_easy_font_print, metni belirtilen konumda (10, screenHeight - 30) oluþturur.
    // Çýktý, fontBuffer'a yazýlýr ve üretilen dörtgen sayýsý (num_quads) döndürülür.
    int num_quads = stb_easy_font_print(10, screenHeight - 30, (char*)currentText.c_str(), NULL, fontBuffer, sizeof(fontBuffer));

    // Her dörtgeni iki üçgene dönüþtürmek için bir vektör oluþtur.
    // Her dörtgen 2 üçgen ve her üçgen 3 köþe içerir, yani 6 köþe.
    // Her köþe sadece 2 float (x,y) pozisyon verisi tutacak.
    std::vector<float> triangleVertices;
    triangleVertices.reserve(num_quads * 6 * 2); // Performans için yaklaþýk rezervasyon

    // stb_easy_font çýktýsýný al ve üçgenlere dönüþtür
    for (int i = 0; i < num_quads; ++i) {
        // Her dörtgen (quad) 4 köþe içerir: V0, V1, V2, V3
        // fontBuffer'daki format: (V0_x, V0_y, V0_s, V0_t), (V1_x, V1_y, V1_s, V1_t), ...
        // Her köþe 4 float (16 byte) yer kaplar.

        // Mevcut dörtgenin fontBuffer içindeki baþlangýç indeksi (float cinsinden)
        int quad_start_idx = i * 4 * 4; // i. dörtgen * 4 köþe/dörtgen * 4 float/köþe

        // Dörtgenin köþe pozisyonlarýný al (sadece x,y koordinatlarýný alýyoruz)
        float v0x = fontBuffer[quad_start_idx + 0];
        float v0y = fontBuffer[quad_start_idx + 1];

        float v1x = fontBuffer[quad_start_idx + 4];
        float v1y = fontBuffer[quad_start_idx + 5];

        float v2x = fontBuffer[quad_start_idx + 8];
        float v2y = fontBuffer[quad_start_idx + 9];

        float v3x = fontBuffer[quad_start_idx + 12];
        float v3y = fontBuffer[quad_start_idx + 13];

        // Birinci üçgeni oluþtur: V0, V1, V2
        triangleVertices.push_back(v0x); triangleVertices.push_back(v0y);
        triangleVertices.push_back(v1x); triangleVertices.push_back(v1y);
        triangleVertices.push_back(v2x); triangleVertices.push_back(v2y);

        // Ýkinci üçgeni oluþtur: V0, V2, V3
        triangleVertices.push_back(v0x); triangleVertices.push_back(v0y);
        triangleVertices.push_back(v2x); triangleVertices.push_back(v2y);
        triangleVertices.push_back(v3x); triangleVertices.push_back(v3y);
    }

    // Modern OpenGL ayarlarý
    glDisable(GL_DEPTH_TEST); // Metnin diðer objelerin önünde görünmesini saðla
    // glDisable(GL_LIGHTING); // Modern OpenGL'de sabit aydýnlatma boru hattý yoktur

    // Shader programýný etkinleþtir
    glUseProgram(shaderProgram);

    // Ekran boyutlarýna göre ortografik projeksiyon matrisi oluþtur
    // Bu, 2D UI elemanlarýný ekran koordinatlarýnda doðru þekilde konumlandýrmayý saðlar.
    //glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
    glm::mat4 projection = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f);

    // Projeksiyon matrisini shader'daki "projection" uniform deðiþkenine gönder
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Üçgenlenmiþ vertex verilerini VBO'ya yükle
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, triangleVertices.size() * sizeof(float), triangleVertices.data(), GL_STREAM_DRAW);

    // VAO'yu baðla (önceden tanýmlanmýþ öznitelik ayarlarý yeniden uygulanýr)
    glBindVertexArray(VAO);

    // OpenGL'e üçgenleri çizmesini söyle
    // Toplam köþe sayýsý: num_quads (dörtgen) * 2 (üçgen/dörtgen) * 3 (köþe/üçgen) = num_quads * 6
    glDrawArrays(GL_TRIANGLES, 0, num_quads * 6);
    glBindVertexArray(0); // VAO baðlamasýný sýfýrla

    glUseProgram(0); // Shader programýný devre dýþý býrak

    glEnable(GL_DEPTH_TEST); // Derinlik testini tekrar etkinleþtir
}

// ---
// ### Yardýmcý Fonksiyonlar

// Shader'ý derlemek için yardýmcý fonksiyon
unsigned int UI::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type); // Shader nesnesi oluþtur
    const char* src = source.c_str();      // Kaynak kodu iþaretçisi
    glShaderSource(id, 1, &src, nullptr);   // Shader kaynaðýný ata
    glCompileShader(id);                    // Shader'ý derle

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); // Derleme durumunu sorgula
    if (result == GL_FALSE) { // Eðer derleme baþarýsýzsa
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); // Hata mesajý uzunluðunu al
        char* message = (char*)alloca(length * sizeof(char)); // Mesaj için bellek ayýr
        glGetShaderInfoLog(id, length, &length, message);     // Hata mesajýný al
        // Hata mesajýný konsola yazdýr
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(id); // Shader'ý sil
        return 0;           // 0 döndür (hata kodu)
    }
    return id; // Derlenmiþ shader ID'sini döndür
}

// Shader programýný oluþturmak için yardýmcý fonksiyon
unsigned int UI::createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    unsigned int program = glCreateProgram(); // Yeni bir shader programý oluþtur
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);   // Vertex shader'ý derle
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource); // Fragment shader'ý derle

    glAttachShader(program, vs); // Vertex shader'ý programa ekle
    glAttachShader(program, fs); // Fragment shader'ý programa ekle
    glLinkProgram(program);      // Programý baðla
    glValidateProgram(program);  // Programý doðrula (hata ayýklama için faydalý)

    glDeleteShader(vs); // Shaderlarý programa baðladýktan sonra silebiliriz
    glDeleteShader(fs); // Bellek boþaltma

    return program; // Shader programýnýn ID'sini döndür
}

