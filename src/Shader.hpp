// Shader.hpp
#pragma once
#include <string>

class Shader {
public:
    unsigned int ID;

    // Shader dosyalar�n� al�p derleyen constructor
    Shader(const char* vertexPath, const char* fragmentPath);

    // Shader program�n� aktif hale getir
    void use() const;

    // Uniform g�nderme fonksiyonlar�
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setMat4(const std::string& name, const float* value) const;
};
