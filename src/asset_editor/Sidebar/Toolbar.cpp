/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Toolbar
*/

#include "Toolbar.hpp"

Edition::Toolbar::Toolbar()
{
}

Edition::Toolbar::~Toolbar()
{
}

void Edition::Toolbar::displayUndoButton(sf::RenderWindow &window)
{
    (void)window;
}

void Edition::Toolbar::displayRedoButton(sf::RenderWindow &window)
{
    (void)window;
}

void Edition::Toolbar::displaySaveButton(sf::RenderWindow &window)
{
    (void)window;
}

void Edition::Toolbar::displayDeleteButton(sf::RenderWindow &window)
{
    (void)window;
}

void Edition::Toolbar::displayMoveButton(sf::RenderWindow &window)
{
    (void)window;
}

void Edition::Toolbar::displayZoomButton(sf::RenderWindow &window)
{
    (void)window;
}

void Edition::Toolbar::displayDezoomButton(sf::RenderWindow &window)
{
    (void)window;
}

void Edition::Toolbar::displayToolbarContainer(sf::RenderWindow &window)
{
    static float currentWidth = window.getSize().x;
    float targetWidth = window.getSize().x;
    float transitionSpeed = 10.0f; // Adjust this value for faster/slower transition

    if (currentWidth != targetWidth) {
        if (currentWidth < targetWidth) {
            currentWidth += transitionSpeed;
            if (currentWidth > targetWidth) currentWidth = targetWidth;
        } else {
            currentWidth -= transitionSpeed;
            if (currentWidth < targetWidth) currentWidth = targetWidth;
        }
    }

    unsigned int toolbarHeight = 50;

    sf::RectangleShape toolbar(sf::Vector2f(currentWidth, toolbarHeight));
    toolbar.setFillColor(sf::Color(50, 50, 50));
    toolbar.setPosition(0, 0);

    // Set border
    toolbar.setOutlineThickness(1);
    toolbar.setOutlineColor(sf::Color::White);

    window.draw(toolbar);
}

void Edition::Toolbar::draw(sf::RenderWindow &window)
{
    this->displayToolbarContainer(window);
    this->displayUndoButton(window);
    this->displayRedoButton(window);
    this->displaySaveButton(window);
    this->displayDeleteButton(window);
    this->displayMoveButton(window);
    this->displayZoomButton(window);
    this->displayDezoomButton(window);
}
