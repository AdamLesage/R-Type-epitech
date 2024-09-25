/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/

#include "Settings.hpp"

Settings::Settings()
{
}

Settings::Settings(std::shared_ptr<sf::RenderWindow> window)
{
    window = window;
}

Settings::~Settings()
{
}

void Settings::displaySettings()
{
    std::cout << "Settings" << std::endl;
}