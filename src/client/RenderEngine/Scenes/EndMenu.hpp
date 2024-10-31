/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** EndMenu
*/

#ifndef ENDMENU_HPP_
#define ENDMENU_HPP_

#include <iostream>
#include <cstring>
#include <array>
#include <memory>
#include <libconfig.h++>
#include <SFML/Graphics.hpp>

#include "../ARenderEngineScene.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace RType {
    /**
     * @class EndMenu display screen for end menu for every game according to cfg file
     */
    class EndMenu : public ARenderEngineScene {
        public:
            /**
             * @brief Construct a new EndMenu object.
             *
             * @param _window The window to display the EndMenu on.
             */
            EndMenu(std::shared_ptr<sf::RenderWindow> window);

            /**
             * @brief Destroy the Lobby object.
             */
            ~EndMenu();

            void runScene(float &latency) override;

            /**
             * @brief Set the game selected
             * 
             * @param gameSelected the game selected
             */
            void setGameSelected(const std::string& gameSelected);

            /**
             * @brief Display the background of the end game menu
             */
            void displayBackground();

            /**
             * @brief Display options wich can be: Play again, Menu, Exit
             */
            void displayEndMenuOptions();
        protected:
        private:
            libconfig::Config _cfg; // The config file
            std::shared_ptr<sf::RenderWindow> _window;
            std::string _gameSelected;
            std::array<std::string, 3> _options; // Play again, Menu, Exit
            unsigned short int _selectedOption; 
            sf::Font _font;
    };
}

#endif /* !ENDMENU_HPP_ */
