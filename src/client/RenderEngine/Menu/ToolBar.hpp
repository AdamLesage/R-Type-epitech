/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** ToolBar
*/

#ifndef TOOLBAR_HPP_
#define TOOLBAR_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

class ToolBar {
    public:
        ToolBar();
        ~ToolBar();

        /**
         * @brief Draw the toolbar.
         */
        void draw(sf::RenderWindow& window);

        /**
         * @brief Draw the toolbar.
         */
        void open();

        /**
         * @brief Handles the events of the toolbar.
         */
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    private:
        bool isVisible;
        sf::RectangleShape toolbarShape;
        sf::Font font;
        sf::Text text;
        sf::RectangleShape dropdownShape;
        bool dropdownOpen;
        std::map<std::string, sf::Text> menuOptions;
};

#endif /* !TOOLBAR_HPP_ */
