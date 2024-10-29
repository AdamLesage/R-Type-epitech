/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ToolbarButton
*/

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define LIB_EXTENSION ".dll"
#define PATH_SEPARATOR "\\"
#else
#include <dlfcn.h>
#define LIB_EXTENSION ".so"
#define PATH_SEPARATOR "/"
#endif

#include "ToolbarButton.hpp"

Edition::ToolbarButton::ToolbarButton(std::string buttonIconAssetPath, sf::Vector2f position) {
    _buttonIconAssetPath = buttonIconAssetPath;

    // Load the texture of the button icon
    _buttonIconTexture = std::make_shared<sf::Texture>();
    if (!_buttonIconTexture->loadFromFile(buttonIconAssetPath)) {
        std::cerr << "Error loading texture " << buttonIconAssetPath << std::endl;
        return;
    }

    _buttonIconSprite.setTexture(*_buttonIconTexture);

    // Set the position of the button
    _size            = sf::Vector2f(40, 40);
    _position        = position;
    _backgroundColor = sf::Color(50, 50, 50);

    _backgroundRectangle.setSize(_size);
    _backgroundRectangle.setPosition(_position);
    _backgroundRectangle.setFillColor(_backgroundColor);
    _backgroundRectangle.setOutlineThickness(1);
    _backgroundRectangle.setOutlineColor(sf::Color::White);

    // Adjust the scale and position of the icon sprite
    sf::FloatRect backgroundBounds = _backgroundRectangle.getGlobalBounds();
    sf::FloatRect iconBounds       = _buttonIconSprite.getGlobalBounds();
    // Adjust the scale of the icon sprite to fit the rectangle
    float scaleX = backgroundBounds.width / iconBounds.width;
    float scaleY = backgroundBounds.height / iconBounds.height;
    _buttonIconSprite.setScale(scaleX, scaleY);

    // Adjust the position of the icon sprite to be centered in the rectangle
    _buttonIconSprite.setPosition(
        backgroundBounds.left + (backgroundBounds.width - iconBounds.width * scaleX) / 2,
        backgroundBounds.top + (backgroundBounds.height - iconBounds.height * scaleY) / 2);
}

std::string Edition::ToolbarButton::update(sf::RenderWindow& window, CurrentSelection& currentSelection) {
    static sf::Clock clickCooldownClock;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::FloatRect bounds       = _backgroundRectangle.getGlobalBounds();
    sf::Cursor cursor;

    // Check if the mouse is hovering over the button
    if (bounds.contains(static_cast<sf::Vector2f>(mousePosition))) {
        _backgroundRectangle.setFillColor(sf::Color(100, 100, 100));

        // Load and set the hand cursor for hover effect
        if (cursor.loadFromSystem(sf::Cursor::Hand)) {
            window.setMouseCursor(cursor);
        }

        // Check if the mouse button is pressed while hovering and cooldown has passed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
            && clickCooldownClock.getElapsedTime().asSeconds() > 0.15f) {
            _backgroundRectangle.setFillColor(sf::Color(175, 175, 175));
            clickCooldownClock.restart();
            return _buttonIconAssetPath;
        }
        return "hovered";
    } else {
        std::string selectionStr =
            _buttonIconAssetPath.substr(_buttonIconAssetPath.find_last_of(PATH_SEPARATOR) + 1);
        if (selectionStr == "undo.png" && currentSelection == UNDO)
            _backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
        else if (selectionStr == "redo.png" && currentSelection == REDO)
            _backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
        else if (selectionStr == "save.png" && currentSelection == SAVE)
            _backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
        else if (selectionStr == "delete.png" && currentSelection == DELETE)
            _backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
        else if (selectionStr == "move.png" && currentSelection == MOVE)
            _backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
        else if (selectionStr == "zoom.png" && currentSelection == ZOOM)
            _backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
        else if (selectionStr == "dezoom.png" && currentSelection == DEZOOM)
            _backgroundRectangle.setFillColor(sf::Color(100, 100, 100));
        else
            _backgroundRectangle.setFillColor(_backgroundColor);
    }
    return "";
}

void Edition::ToolbarButton::draw(sf::RenderWindow& window) {
    window.draw(_backgroundRectangle);
    window.draw(_buttonIconSprite);
}

Edition::ToolbarButton::~ToolbarButton() {
}
