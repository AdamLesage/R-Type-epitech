/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** EditionScreen
*/

#include "EditionScreen.hpp"


Edition::EditionScreen::EditionScreen()
{
    _centralArea.setSize(sf::Vector2f(1350, 900));
    _centralArea.setPosition(20, 100);
    _centralArea.setFillColor(sf::Color(50, 50, 50));
    _centralArea.setOutlineThickness(1);
    _centralArea.setOutlineColor(sf::Color::White);
}

Edition::EditionScreen::~EditionScreen()
{
}

void Edition::EditionScreen::draw(sf::RenderWindow &window)
{
    window.draw(_centralArea);

    for (const auto &asset : _assets) {
        asset->draw(window);
    }
}

void Edition::EditionScreen::handleEvent(const sf::Event &event)
{
    (void)event;
}
