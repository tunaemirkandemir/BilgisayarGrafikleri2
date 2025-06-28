#pragma once
#include <string>

class SoundSystem {
public:
    void playOnce(const std::string& filename);         // Tek seferlik ses çal
    void playLoop(const std::string& filename);         // Sonsuz döngüde çal   
    void stop();                                        // Her þeyi durdur
};
