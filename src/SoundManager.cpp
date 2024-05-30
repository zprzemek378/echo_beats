//
// Created by Przemysław Zieliński on 28.05.2024.
//

#include "SoundManager.h"

SoundManager::SoundManager() : sound(std::make_unique<sf::Sound>()) {
    for (int i = 0; i <= 7; ++i) {
        sf::SoundBuffer buffer;
        buffer.loadFromFile("../sounds/sound" + std::to_string(i+1) + ".wav");
        soundBuffers.push_back(buffer);
    }
}


void SoundManager::playSound(int soundIndex) {
    if (soundIndex >= 0 && soundIndex < soundBuffers.size()) {
        sound->stop();
        sound->setBuffer(soundBuffers[soundIndex]);
        sound->play();
    } else {
        std::cerr << "Index " << soundIndex << " not found" << std::endl;
    }
}

