/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Asset
*/

#include "Asset.hpp"

Edition::Asset::Asset(int x, int y, std::string assetPath, size_t entityCode)
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
    this->addComponent<Sprite>(Sprite{assetPath, {static_cast<int>(_spriteTexture->getSize().x), static_cast<int>(_spriteTexture->getSize().y)}, {0, 0}});

    this->_sprite.setTexture(_spriteTexture);
    this->_entityCode = "0x" + std::to_string(entityCode);
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
    auto &sprite = this->getComponent<Sprite>();
    auto &size = this->getComponent<Size>();
    auto &pos = this->getComponent<Position>();

    this->_sprite.setPosition(pos.x, pos.y);
    this->_sprite.setSize(sf::Vector2f(size.x, size.y));
    this->_sprite.setTextureRect(sf::IntRect(sprite.rectPos[0], sprite.rectPos[1], sprite.rectSize[0], sprite.rectSize[1]));
    this->_sprite.setRotation(this->getComponent<Rotation>().rotation);
    window.draw(this->_sprite);
}

sf::FloatRect Edition::Asset::getGlobalBounds()
{
    return (this->_sprite.getGlobalBounds());
}

void Edition::Asset::setSpriteTexture(std::string assetPath)
{
    _spriteTexture = new sf::Texture();
    if (!_spriteTexture->loadFromFile(assetPath)) {
        std::cerr << "Failed to load texture from " << assetPath << std::endl;
        return;
    }
    this->_sprite.setTexture(_spriteTexture);
    this->_sprite.setSize(sf::Vector2f(this->getComponent<Size>().x, this->getComponent<Size>().y));
}
