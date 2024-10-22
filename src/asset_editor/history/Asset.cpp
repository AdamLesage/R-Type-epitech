/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Asset
*/

#include "Asset.hpp"

Edition::Asset::Asset(int x, int y, std::string assetPath)
{
    this->_assetPath = assetPath;
    _spriteTexture = new sf::Texture();
    if (!_spriteTexture->loadFromFile(_assetPath)) {
        std::cerr << "Failed to load texture from " << _assetPath << std::endl;
        return;
    }
    this->addComponent<Position>(Position{static_cast<float>(x), static_cast<float>(y)});
    this->addComponent<Size>(Size{_spriteTexture->getSize().x, _spriteTexture->getSize().y});
    this->addComponent<Rotation>(Rotation{0});

    this->_sprite.setTexture(_spriteTexture);
    this->_sprite.setSize(sf::Vector2f(this->getComponent<Size>().x, this->getComponent<Size>().y));
}

Edition::Asset::~Asset()
{
}

void Edition::Asset::move(int dx, int dy)
{
    this->getComponent<Position>().x = dx;
    this->getComponent<Position>().y = dy;
}

void Edition::Asset::draw(sf::RenderWindow &window)
{
    this->_sprite.setPosition(this->getComponent<Position>().x, this->getComponent<Position>().y);
    this->_sprite.setSize(sf::Vector2f(this->getComponent<Size>().x, this->getComponent<Size>().y));
    this->_sprite.setRotation(this->getComponent<Rotation>().rotation);
    window.draw(this->_sprite);
}

sf::FloatRect Edition::Asset::getGlobalBounds()
{
    return (this->_sprite.getGlobalBounds());
}
