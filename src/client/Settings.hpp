/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class Settings {
    public:
        Settings();
        Settings(std::shared_ptr<sf::RenderWindow> window);
        ~Settings();
        void displaySettings();
    protected:
    private:
};

#endif /* !SETTINGS_HPP_ */
