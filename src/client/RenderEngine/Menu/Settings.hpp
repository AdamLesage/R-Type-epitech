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
        /**
         * @brief Construct a new Settings object.
         *
         * @param _window The window to display the settings on.
         */
        Settings(std::shared_ptr<sf::RenderWindow> _window);

        /**
         * @brief Destroy the Settings object.
         */
        ~Settings();

        /**
         * @brief Displays the settings.
         */
        void displaySettings();

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
         * @brief Changes the key of the selected option.
         *
         * @param key The new key.
         */
        void changeKey(std::string key);

        /**
         * @brief Displays the settings.
         */
        void display();
    protected:
        int selectedOption;
        sf::Sound selectSound;
        std::shared_ptr<sf::RenderWindow> window;
        sf::Font font;
        sf::Text menuOptions[6];
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::Event event;
        sf::RectangleShape background;
        sf::Texture backgroundTexture;
    private:
};

#endif /* !SETTINGS_HPP_ */
