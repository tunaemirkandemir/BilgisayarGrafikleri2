// Texture.hpp
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glad/glad.h>

unsigned int LoadTexture(const std::string& path, bool alpha = false);

#endif
