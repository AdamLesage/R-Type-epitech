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

Game::Game(std::shared_ptr<sf::RenderWindow> window) : window(std::move(window)), currentFrame(1), frameDuration(0.05f), animationComplete(false)
{
    if (!font.loadFromFile("asset/r-type.ttf")) {
        throw std::runtime_error("Error loading font");
    }

    gameInProgressText.setFont(font);
    gameInProgressText.setString("Game in Progress");
    gameInProgressText.setCharacterSize(60);
    gameInProgressText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = gameInProgressText.getLocalBounds();
    gameInProgressText.setOrigin(textRect.width / 2, textRect.height / 2);
    gameInProgressText.setPosition(window->getSize().x / 2, window->getSize().y / 2);
}

Game::~Game()
{
}

void Game::displayGame()
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;

    if (!window) {
        std::cerr << "Error: Window not initialized!" << std::endl;
        return;
    }

    while (window->isOpen()) {
        handleEvents();

        if (!animationComplete) {
            if (clock.getElapsedTime().asSeconds() > frameDuration) {
                if (!loadFrameTexture(texture, sprite)) {
                    return;
                }
                clock.restart();
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

void Game::handleEvents()
{
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

bool Game::loadFrameTexture(sf::Texture& texture, sf::Sprite& sprite)
{
    std::ostringstream oss;
    oss << "asset/game_launch/Sans titre (1)_" << std::setw(3) << std::setfill('0') << currentFrame << ".jpg";
    std::string filename = oss.str();

    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error loading " << filename << std::endl;
        return false;
    }

    sprite.setTexture(texture);
    currentFrame++;

    if (currentFrame > 151) {
        animationComplete = true;
    }

    return true;
}
