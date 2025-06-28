#include "Texture.hpp"
#include "stb_image.h"
#include <iostream>
#include <filesystem>

unsigned int LoadTexture(const std::string& path, bool alpha) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // PNG dosyalarý için
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    std::cout << "Çalýþma dizini: " << std::filesystem::current_path() << std::endl;
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Wrap ve filtre ayarlarý
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else {
        std::cerr << "Texture loading failed: " << path << std::endl;
        std::cerr << "STB error: " << stbi_failure_reason() << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
