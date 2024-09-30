/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Button.hpp"
class Settings {
    public:
        Settings();
        Settings(std::shared_ptr<sf::RenderWindow> window);
        ~Settings();
        void displaySettings();
        void moveUp();
        void moveDown();
        int getSelectedOption() const;
        void changeKey(std::string key);
        void display();
    protected:
        int selectedOption;
        sf::Sound selectSound;
        std::shared_ptr<sf::RenderWindow> window;
        sf::Font font;
        sf::Text menuOptions[6];
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        std::vector<std::shared_ptr<Button>> buttons;
        sf::Event event;
    private:
};

#endif /* !SETTINGS_HPP_ */
