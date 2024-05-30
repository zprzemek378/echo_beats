//
// Created by Przemysław Zieliński on 28.05.2024.
//

#ifndef ECHO_BEATS_SOUNDMANAGER_H
#define ECHO_BEATS_SOUNDMANAGER_H


#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

class SoundManager {
public:
    SoundManager();
    void playSound(int soundIndex);

private:
    std::vector<sf::SoundBuffer> soundBuffers;
    std::unique_ptr<sf::Sound> sound;
};



#endif //ECHO_BEATS_SOUNDMANAGER_H
