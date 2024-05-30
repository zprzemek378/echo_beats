//
// Created by Przemysław Zieliński on 28.05.2024.
//

#include "Game.h"


Game::Game() :
    window(sf::VideoMode(800, 415), "Echo Beats"),
    backGroundColor(180,180,180),
    releasedKeyColor(30,30,30),
    pressedKeyColor(100,100,100) {

    previousScore = 0;
    pressedKey = -1;
    previousKey = -1;
    userCanPress = true;
    triggerNextLevel = false;
    level = 0;
    pressedInThisLevel = 0;
    font.loadFromFile("../font/Poppins-Black.ttf");

    highestScore = readHighScore();
    gameOverDisplay = false;
    nextLevelDisplay = false;
    pressedButton = false;
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    while (window.pollEvent(event)) {
        if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            pressedButton = false;
        }


        if (event.type == sf::Event::Closed) {
            window.close();
        } else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !triggerNextLevel && level == 0 && startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            pressedButton = true;
        } else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !triggerNextLevel && level == 0 && startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            triggerNextLevel = true;
        } else if (userCanPress && event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Num1:
                    pressedKey = 0;
                    break;
                case sf::Keyboard::Num2:
                    pressedKey = 1;
                    break;
                case sf::Keyboard::Num3:
                    pressedKey = 2;
                    break;
                case sf::Keyboard::Num4:
                    pressedKey = 3;
                    break;
                case sf::Keyboard::Num5:
                    pressedKey = 4;
                    break;
                case sf::Keyboard::Num6:
                    pressedKey = 5;
                    break;
                case sf::Keyboard::Num7:
                    pressedKey = 6;
                    break;
                case sf::Keyboard::Num8:
                    pressedKey = 7;
                    break;
                default:
                    pressedKey = -1;
            }
        } else if(userCanPress && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            for (int i = 0; i < 8; i++) {
                if (keys[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    pressedKey = i;
                }
            }
        } else if(userCanPress && (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased)) {
            pressedKey = -1;
        }

    }
}

//  W ODDZIELNYM WĄTKU
void Game::nextLevel() {
    std::cout << "Next level!" << std::endl;
    userCanPress = false;
    nextLevelDisplay = true;
    pressedInThisLevel = 0;
    level++;
    sequence.addElement();


    std::this_thread::sleep_for(std::chrono::seconds(1));
    pressedKey = -1;


    std::this_thread::sleep_for(std::chrono::seconds(1));
    nextLevelDisplay = false;

    for (int i = 0; i < level; i++) {
        pressedKey = sequence.getElement(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        pressedKey = -1;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    userCanPress = true;
}

void Game::gameOver() {
    std::cout << "Game Over!" << std::endl;
    previousScore = level-1;
    gameOverDisplay = true;


    if(previousScore > highestScore) {
        highestScore = previousScore;
        saveHighScore(highestScore);
    }

    std::this_thread::sleep_for(std::chrono::seconds(4));

    sequence.reset();
    pressedKey = -1;
    previousKey = -1;
    level = 0;
    pressedInThisLevel = 0;

    gameOverDisplay = false;


}

void Game::update() {
    if(triggerNextLevel) {
        triggerNextLevel = false;
        userCanPress = false;
        std::thread(&Game::nextLevel, this).detach();
    }

    if(userCanPress) {
        if(level == pressedInThisLevel && level != 0) {
            triggerNextLevel = true;
        }
        else if (pressedKey != -1 && pressedKey != previousKey && level != 0) {
            if(pressedKey == sequence.getElement(pressedInThisLevel)) {
                pressedInThisLevel++;
            } else {
                userCanPress = false;
                std::thread(&Game::gameOver, this).detach();
            }
        }
    }
}

void Game::render() {
    window.clear(backGroundColor);

    //PRZYCISK
    if(!triggerNextLevel && level == 0) {
        userCanPress = true;
        sf::RectangleShape button(sf::Vector2f(140.f, 50.f));

        if (pressedButton) { button.setFillColor(pressedKeyColor); }
        else { button.setFillColor(releasedKeyColor); }

        button.setPosition(640.f, 20.f);
        window.draw(button);

        sf::Text buttonText;
        buttonText.setFont(font);
        std::stringstream ss1;
        ss1 << "START";
        buttonText.setString(ss1.str());
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);

        sf::FloatRect textRect = buttonText.getLocalBounds();
        buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        buttonText.setPosition(button.getPosition().x + button.getSize().x / 2.0f,
                               button.getPosition().y + button.getSize().y / 2.0f);

        startButton = button;

        window.draw(buttonText);
    }



    // DŹWIĘK
    if (pressedKey != -1 && pressedKey != previousKey) {
        soundManager.playSound(pressedKey);
        previousKey = pressedKey;
    } else if (pressedKey == -1) {
        previousKey = -1;
    }

    keys.clear();
    // OBRAZ
    float currentPosition = 105;
    for(int i=0; i<8; i++) {
        if(i == pressedKey) {
            sf::RectangleShape square(sf::Vector2f(65.f, 160.f));
            square.setFillColor(pressedKeyColor);
            square.setPosition(currentPosition, 215.f);
            keys.push_back(square);
            window.draw(square);
        } else {
            sf::RectangleShape square(sf::Vector2f(65.f, 180.f));
            square.setFillColor(releasedKeyColor);
            square.setPosition(currentPosition, 215.f);
            keys.push_back(square);
            window.draw(square);
        }

        currentPosition+=75;

    }

    sf::Text text;

    text.setFont(font);
    std::stringstream ss;
    ss << "Highest score: " << highestScore << std::endl << "Level: " << level << std::endl;
    if(gameOverDisplay) ss << std::endl << "Game Over! Your score: " << previousScore << "." << std::endl;
    if(nextLevelDisplay && level != 1) ss << std::endl << "Great! Starting level " << level << "..." << std::endl;
    if(nextLevelDisplay && level == 1) ss << std::endl << "Let's begin! Starting level " << level << "..." << std::endl;
    text.setString(ss.str());
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(20.f, 20.f);
    window.draw(text);

    window.display();
}

void Game::saveHighScore(int score) {
    std::ofstream file("../highscore.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

int Game::readHighScore() {
    std::ifstream file("../highscore.txt");

    int highestScoreLoc = 0;
    if (file.is_open()) {
        std::string scoreStr;
        if (std::getline(file, scoreStr)) {
            try {
                highestScoreLoc = std::stoi(scoreStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid high score value in file." << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "High score value out of range." << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for reading." << std::endl;
    }
    return highestScoreLoc;
}