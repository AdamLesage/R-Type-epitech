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

std::shared_ptr<Edition::Asset> Edition::EditionScreen::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (auto& it: _assets) {
            // if (it->getGlobalBounds().contains((event.mouseButton.x), (event.mouseButton.y))) {
            //     return (it);
            // }
        }
    }
    return nullptr;
}
