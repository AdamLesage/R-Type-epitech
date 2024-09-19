/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Color
*/

#include "Color.hpp"
#include <stdlib.h>
#include <time.h>

Component::Color::Color()
{
    srand(time(NULL));
    _color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
}

Component::Color::~Color()
{
}
