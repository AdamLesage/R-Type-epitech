/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Asset
*/

#include "Asset.hpp"

Edition::Asset::Asset(int x, int y, std::string assetPath)
{
    this->_x = x;
    this->_y = y;
    this->_assetPath = assetPath;
    _spriteTexture = sf::Texture();
    if (!_spriteTexture.loadFromFile(_assetPath)) {
        std::cerr << "Failed to load texture from " << _assetPath << std::endl;
        return;
    }
    this->_sprite.setTexture(_spriteTexture);
}

Edition::Asset::~Asset()
{
}

void Edition::Asset::move(int dx, int dy)
{
    _x = dx;
    _y = dy;
}

void Edition::Asset::draw(sf::RenderWindow &window)
{
    this->_sprite.setPosition(_x, _y);
    window.draw(this->_sprite);
}

sf::FloatRect Edition::Asset::getGlobalBounds()
{
    return (this->_sprite.getGlobalBounds());
}
