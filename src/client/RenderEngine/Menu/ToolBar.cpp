/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** ToolBar
*/

#include "ToolBar.hpp"

ToolBar::ToolBar() : isVisible(false)
{
    toolbarShape.setSize({1920, 50});
    toolbarShape.setFillColor(sf::Color(50,50,50));

    if (!font.loadFromFile("./assets/r-type.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

ToolBar::~ToolBar()
{
}

void ToolBar::open()
{
    isVisible = !isVisible;
}

void ToolBar::draw(sf::RenderWindow& window)
{
    if (isVisible) {
        window.draw(toolbarShape);
    }
}
