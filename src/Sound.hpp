#pragma once
#include <string>

class SoundSystem {
public:
    void playOnce(const std::string& filename);         // Tek seferlik ses �al
    void playLoop(const std::string& filename);         // Sonsuz d�ng�de �al   
    void stop();                                        // Her �eyi durdur
};
