/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** GameMetrics
*/

#include "GameMetrics.hpp"
#include <iostream>

GameMetrics::GameMetrics()
{
}

GameMetrics::~GameMetrics()
{
}

void GameMetrics::displayFPS(sf::RenderWindow& window)
{
    static sf::Clock clock;
    static int frameCnt = 0;
    static int fps = 0;
    sf::Text text;
    static sf::Font font;

    frameCnt += 1;
    if (!font.loadFromFile("./assets/r-type.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    if (clock.getElapsedTime().asSeconds() >= 1.0f) {
        fps = frameCnt / clock.getElapsedTime().asSeconds();
        frameCnt = 0;
        clock.restart();
    }
    text.setFont(font);
    text.setString("FPS: " + std::to_string(fps));
    text.setFillColor(sf::Color::White);
    text.setPosition(0, 0);
    window.draw(text);
}
