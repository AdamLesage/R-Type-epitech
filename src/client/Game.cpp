/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Game::Game()
{
}

Game::Game(std::shared_ptr<sf::RenderWindow> window)
{
    this->window = window;
}

Game::~Game()
{
}

void Game::displayGame()
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Font font;
    sf::Text gameInProgressText;

    int currentFrame = 1;
    sf::Clock clock;
    float frameDuration = 0.05f;
    bool animationComplete = false;

    if (!window) {
        std::cerr << "Error: Window not initialized!" << std::endl;
        return;
    }

    if (!font.loadFromFile("asset/r-type.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    gameInProgressText.setFont(font);
    gameInProgressText.setString("Game in Progress");
    gameInProgressText.setCharacterSize(60);
    gameInProgressText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = gameInProgressText.getLocalBounds();
    gameInProgressText.setOrigin(textRect.width / 2, textRect.height / 2);
    gameInProgressText.setPosition(window->getSize().x / 2, window->getSize().y / 2);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        if (!animationComplete) {
            if (clock.getElapsedTime().asSeconds() > frameDuration) {
                std::ostringstream oss;
                oss << "asset/game_launch/Sans titre (1)_" << std::setw(3) << std::setfill('0') << currentFrame << ".jpg";
                std::string filename = oss.str();

                if (!texture.loadFromFile(filename)) {
                    std::cerr << "Error loading " << filename << std::endl;
                    return;
                }

                sprite.setTexture(texture);
                currentFrame++;
                clock.restart();
            }

            if (currentFrame > 151) {
                animationComplete = true;
            }
        }

        window->clear();

        if (animationComplete) {
            window->draw(gameInProgressText);
        } else {
            window->draw(sprite);
        }

        window->display();
    }
}
