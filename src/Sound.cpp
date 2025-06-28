#include "Sound.hpp"
#include <windows.h>
#include <mmsystem.h> // PlaySound fonksiyonu için gerekli


void SoundSystem::playOnce(const std::string& filename) {
    PlaySoundA(filename.c_str(), NULL, SND_ASYNC | SND_FILENAME);
}

void SoundSystem::playLoop(const std::string& filename) {
    PlaySoundA(filename.c_str(), NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
}

void SoundSystem::stop() {
    PlaySoundA(NULL, 0, 0); // Her þeyi durdurur
}

