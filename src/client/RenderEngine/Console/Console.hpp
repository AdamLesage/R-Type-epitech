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
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "../../Mediator/IMediator.hpp"
#define PATH_SEPARATOR "/"

namespace RType {
    class Console {
        public:
            Console(std::shared_ptr<sf::RenderWindow> _window, sf::Event _event);
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
             * @brief Toggle the developer console visibility from an event
             * 
             * This function will toggle the developer console visibility if the event is a key press
             * 
             * @param event The event to check
             */
            void toggleDeveloperConsoleFromEvent(sf::Event &event);

            /**
             * @brief Display the developer console
             * 
             * This function will display the developer console thanks to SFML
             */
            void displayDeveloperConsole();

            /**
             * @brief Display the close container button
             * 
             * This function will display a close button at the top right of the container
             */
            void displayCloseContainerButton();
            /**
             * @brief Check Input of user
             * 
             * This function will check if the user want to type something in the console
             */
            bool checkInput();
            /**
             * @brief Check Input of user
             * 
             * This function will check if the user want to type something in the console
             */
            void checkClick();
            /**
             * @brief Check he text of the user is command or not
             * 
             * @return bool Return true if the text is a command and false if not
             * 
             * Verify if the text is an existing command
             */
            bool isCommand();
            /**
             * @brief Print the FPS
             * 
             * Print the FPS
             */
            void displayFPS();
            /**
             * @brief Sets the mediator, it will be used to communicate with the rendering engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator);
            std::shared_ptr<IMediator> _mediator;

        protected:
            bool _showDeveloperConsole;
        private:
            /**
             * @brief Display the container of the developer console
             * 
             * Container is a black rectangle that contains the console with a specific size and opacity to make it visible
             */
            void displayContainer();
            sf::Event event;
            std::shared_ptr<sf::RenderWindow> window;
            std::vector<sf::Text> History;
            std::vector<sf::Text> CommandHistory;
            sf::Text _inputText;
            sf::Font font;
            bool _typing;
            sf::RectangleShape container;
            sf::RectangleShape secondContainer;
            std::string _input;
            sf::Clock clock;  // Pour mesurer le temps écoulé entre chaque frame
            float fps;
            sf::Text FPS;
            bool show_fps;
    };
}

#endif /* !CONSOLE_HPP_ */

