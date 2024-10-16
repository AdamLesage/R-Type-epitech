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

    private:
        bool isVisible;
        sf::RectangleShape toolbarShape;
        sf::Font font;
        sf::Text text;
};

#endif /* !TOOLBAR_HPP_ */
