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
}

Edition::Asset::~Asset()
{
}

void Edition::Asset::move(int dx, int dy)
{
    _x += dx;
    _y += dy;
}

void Edition::Asset::draw(sf::RenderWindow &window)
{
    (void)window;
}
