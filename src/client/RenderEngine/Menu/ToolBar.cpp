/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** ToolBar
*/

#include "ToolBar.hpp"

ToolBar::ToolBar() : isVisible(false), dropdownOpen(false)
{
    toolbarShape.setSize({1920, 50});
    toolbarShape.setFillColor(sf::Color(50,50,50));

    if (!font.loadFromFile("./assets/r-type.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    text.setFont(font);
    text.setString("Overlay");
    text.setPosition(10, 5);
    dropdownShape.setSize({150, 60});
    dropdownShape.setFillColor(sf::Color(70, 70, 70));
    dropdownShape.setPosition(10, 50);
}

ToolBar::~ToolBar()
{
}

void ToolBar::open()
{
    isVisible = !isVisible;
}

void ToolBar::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (text.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            dropdownOpen = !dropdownOpen;
        }
    }
}

void ToolBar::draw(sf::RenderWindow& window)
{
    if (isVisible) {
        window.draw(toolbarShape);
        window.draw(text);
    }
    if (dropdownOpen) {
        window.draw(dropdownShape);
    }
}
