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
#include "Lobby.hpp"

namespace RType {
    class Menu
    {
    public:

        /**
         * @brief Construct a new Menu object.
         *
         * @param _window The window to display the menu on.
         */
        Menu(std::shared_ptr<sf::RenderWindow> wdw);

        /**
         * @brief Destroy the Menu object.
         */
        ~Menu() = default;

        /**
         * @brief Draws the menu.
         */
        void draw();
        /**
         * @brief Moves the selection up.
         */
        void moveUp();
        /**
         * @brief Moves the selection down.
         */
        void moveDown();
        /**
         * @brief Get the selected option.
         *
         * @return int The selected option.
         */
        int getSelectedOption() const;
        /**
         * @brief Displays the menu.
         */
        int displayMenu();

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
        std::shared_ptr<Lobby> lobby;
        // std::shared_ptr<Game> games;
    };
}

#endif /* !MENU_HPP_ */
