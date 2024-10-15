/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ToolbarButton
*/

#include "ToolbarButton.hpp"
Edition::ToolbarButton::ToolbarButton(std::string buttonIconAssetPath, sf::Vector2f position)
{
    _buttonIconAssetPath = buttonIconAssetPath;

    // Load the texture of the button icon
    _buttonIconTexture = std::make_shared<sf::Texture>();
    if (!_buttonIconTexture->loadFromFile(buttonIconAssetPath)) {
        std::cerr << "Erreur lors du chargement de la texture " << buttonIconAssetPath << std::endl;
        return;
    }

    _buttonIconSprite.setTexture(*_buttonIconTexture);

    // Set the position of the button
    _size = sf::Vector2f(40, 40);
    _position = position;
    _backgroundColor = sf::Color(50, 50, 50);

    _backgroundRectangle.setSize(_size);
    _backgroundRectangle.setPosition(_position);
    _backgroundRectangle.setFillColor(_backgroundColor);
    _backgroundRectangle.setOutlineThickness(1);
    _backgroundRectangle.setOutlineColor(sf::Color::White);

    // Adjust the scale and position of the icon sprite
    sf::FloatRect backgroundBounds = _backgroundRectangle.getGlobalBounds();
    sf::FloatRect iconBounds = _buttonIconSprite.getGlobalBounds();
    // Adjust the scale of the icon sprite to fit the rectangle
    float scaleX = backgroundBounds.width / iconBounds.width;
    float scaleY = backgroundBounds.height / iconBounds.height;
    _buttonIconSprite.setScale(scaleX, scaleY);

    // Adjust the position of the icon sprite to be centered in the rectangle
    _buttonIconSprite.setPosition(
        backgroundBounds.left + (backgroundBounds.width - iconBounds.width * scaleX) / 2,
        backgroundBounds.top + (backgroundBounds.height - iconBounds.height * scaleY) / 2
    );
}

void Edition::ToolbarButton::draw(sf::RenderWindow &window)
{
    window.draw(_backgroundRectangle);
    window.draw(_buttonIconSprite);
}



Edition::ToolbarButton::~ToolbarButton()
{
}

