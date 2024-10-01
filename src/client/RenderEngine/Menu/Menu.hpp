/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Settings.hpp"
#include "Game.hpp"

namespace RType {
    class Menu
    {
    public:
        Menu();
        ~Menu() = default;
        void draw();
        void moveUp();
        void moveDown();
        int getSelectedOption() const;
        void displayMenu();

    private:
        int selectedOption;
        sf::Font font;
        sf::Text menuOptions[3]; // Play, Settings, Quit
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::SoundBuffer selectBuffer;
        sf::Sound selectSound;
        std::shared_ptr<sf::RenderWindow> window;
        sf::RectangleShape background;
        sf::Texture backgroundTexture;
        std::shared_ptr<Settings> settings;
        std::shared_ptr<Game> games;
    };
}

#endif /* !MENU_HPP_ */
