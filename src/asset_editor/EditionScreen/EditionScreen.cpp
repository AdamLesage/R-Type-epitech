/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** EditionScreen
*/

#include "EditionScreen.hpp"


Edition::EditionScreen::EditionScreen() : _isDragging(false), _selectedAssetIndex(-1)
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
        window.draw(asset);
    }
}

void Edition::EditionScreen::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            // Vérifier si un asset est sélectionné
            for (size_t i = 0; i < _assets.size(); ++i) {
                if (_assets[i].getGlobalBounds().contains(mousePos)) {
                    _isDragging = true;
                    _selectedAssetIndex = i;
                    _dragOffset = mousePos - _assets[i].getPosition();
                    break;
                }
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _isDragging = false;
            _selectedAssetIndex = -1;
        }
    } else if (event.type == sf::Event::MouseMoved) {
        if (_isDragging && _selectedAssetIndex != -1) {
            sf::Vector2f newPos(event.mouseMove.x, event.mouseMove.y);
            _assets[_selectedAssetIndex].setPosition(newPos - _dragOffset);
        }
    }
}
