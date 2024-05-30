//
// Created by Przemysław Zieliński on 28.05.2024.
//

#ifndef ECHO_BEATS_GAME_H
#define ECHO_BEATS_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "SoundManager.h"
#include "Sequence.h"
#include <unistd.h>
#include <fstream>
#include <vector>


class Game {
public:
    Game();
    void run();
private:
    int pressedKey;
    int previousKey;

    bool userCanPress;
    bool triggerNextLevel;
    bool gameOverDisplay;
    bool nextLevelDisplay;
    bool pressedButton;
    int level;
    int pressedInThisLevel;
    int previousScore;
    int highestScore;

    SoundManager soundManager;
    Sequence sequence;

    std::vector<sf::RectangleShape> keys;
    sf::RectangleShape startButton;

    sf::Font font;

    sf::Color backGroundColor;
    sf::Color releasedKeyColor;
    sf::Color pressedKeyColor;

    void nextLevel();
    void gameOver();
    void saveHighScore(int score);
    int readHighScore();

    void processEvents();
    void update();
    void render();
    sf::RenderWindow window;
};


#endif //ECHO_BEATS_GAME_H
