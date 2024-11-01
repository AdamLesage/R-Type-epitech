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
#include "GameMetrics.hpp"
#include <memory>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

class Toolbar {
    public:
        Toolbar();
        ~Toolbar();

        /**
         * @brief Draw the toolbar.
         * 
         * @param window window to draw-in.
         */
        void draw(std::shared_ptr<sf::RenderTexture> renderTexture);

        /**
         * @brief Draw the toolbar.
         */
        void open();

        /**
         * @brief Handles the events of the toolbar.
         * 
         * @param event event informations.
         * @param window window to interact with.
         */
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);

        /**
         * @brief Initialize options to display in Overlay dropdown menu.
         */
        void initializeMenuOptions();

        /**
         * @brief Update the option hovered by the mouse
         * 
         * @param window window to interact with.
         */
        void updateHoveredOption(sf::RenderWindow& window);

        /**
         * @brief Display metrics
         * 
         * @param optionName option's name
         */
        void displayMetrics(const std::string optionName);

        bool showFps;
        bool showMemory;
        bool showCpu;
        bool showGpu;
        bool showNetwork;
        bool showPlayerPos;

    private:
        bool isVisible;
        sf::RectangleShape toolbarShape;
        sf::Font font;
        sf::Text text;
        sf::RectangleShape dropdownShape;
        bool dropdownOpen;
        std::string hoveredOpt;
        std::map<std::string, bool> optionSelected;
        std::map<std::string, sf::Text> menuOptions;
};

#endif /* !TOOLBAR_HPP_ */