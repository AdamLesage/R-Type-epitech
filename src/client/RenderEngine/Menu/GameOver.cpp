/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameOver
*/

#include "GameOver.hpp"

RType::GameOver::GameOver()
{
}

RType::GameOver::GameOver(std::shared_ptr<sf::RenderWindow> _window)
{
    window = _window;
    if (!font.loadFromFile("src/client/asset/r-type.ttf")) {
        return;
    }
    game_over.setCharacterSize(50);
    game_over.setFillColor(sf::Color::White);
    game_over.setFont(font);
    game_over.setOutlineColor(sf::Color::Black);
    game_over.setOutlineThickness(5);
    game_over.setString("GAME OVER");
    game_over.setPosition(sf::Vector2f(1920 / 2, 1080 / 2 ));
    subtitle.setCharacterSize(30);
    subtitle.setFillColor(sf::Color::White);
    subtitle.setFont(font);
    subtitle.setOutlineColor(sf::Color::Black);
    subtitle.setOutlineThickness(5);
    subtitle.setString("Press ESCAPE to join spectate mode");
    subtitle.setPosition(sf::Vector2f(1920 / 2, 1080 / 2 ));
    filter.setFillColor(sf::Color(0, 0, 0, 128));
    filter.setSize(sf::Vector2f(1920, 1080));
}


RType::GameOver::~GameOver()
{
}

void RType::GameOver::display()
{
    window->draw(filter);
    window->draw(game_over);
    window->draw(subtitle);
    window->display();
}

