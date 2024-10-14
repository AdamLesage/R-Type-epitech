/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Console
*/

#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

namespace RType {
    class Console {
        public:
            Console();
            ~Console();

            /**
             * @brief Get the developer console visibility
             * 
             * @return bool Return true if the developer console is visible, false if it's hidden
             */
            bool getDeveloperConsole() const { return _showDeveloperConsole; }

            /**
             * @brief Toggle the developer console visibility
             */
            void toggleDeveloperConsole() { _showDeveloperConsole = !_showDeveloperConsole; }

            /**
             * @brief Display the developer console
             * 
             * This function will display the developer console thanks to SFML
             */
            void displayDeveloperConsole(sf::RenderWindow &window);
        protected:
            bool _showDeveloperConsole;
        private:
            /**
             * @brief Display the container of the developer console
             * 
             * Container is a black rectangle that contains the console with a specific size and opacity to make it visible
             */
            void displayContainer(sf::RenderWindow &window);
    };
}

#endif /* !CONSOLE_HPP_ */
