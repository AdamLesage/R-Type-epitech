/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ClientConnexionHandling
*/

#ifndef CLIENTCONNEXIONHANDLING_HPP_
#define CLIENTCONNEXIONHANDLING_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace RType {
    /**
     * @brief Class will display the window to retrieve the server ip and port
     * @author Adam Lesage
     */
    class ClientConnexionHandling {
        public:
            /**
             * @brief Construct a new Client Connexion Handling object
             * @author Adam Lesage
             */
            ClientConnexionHandling(std::string host = "", unsigned short server_port = 0);

            /**
             * @brief Destroy the Client Connexion Handling object
             * @author Adam Lesage
             */
            ~ClientConnexionHandling();

            /**
             * @brief Display the connexion window
             * @author Adam Lesage
             */
            void displayConnexionWindow();

            /**
             * @brief Display the background
             * @author Adam Lesage
             */
            void displayBackground();

            /**
             * @brief Display the input text for the host
             * @author Adam Lesage
             */
            void displayInputTextHost();

            /**
             * @brief Display the input text for the port
             * @author Adam Lesage
             */
            void displayInputTextPort();

            /**
             * @brief Display the submit button
             * @author Adam Lesage
             */
            void displaySubmitButton();

            /**
             * @brief Display the error message if the host or port are invalid
             * @author Adam Lesage
             */
            void displayError();

            /**
             * @brief Display the game selection
             *
             * Choices are "R-Type" and "Platformer"
             * @author Adam Lesage
             */
            void displayGameSelection();

            /**
             * @brief display button to toggle mode offline
             *
             * Can click on button to toggle mode offline
             *
             * @author Adam Lesage
             */
            void displayModeOffline();

            /**
             * @brief Retrieve the input text for the host
             *
             * @param event The event to retrieve
             * @author Adam Lesage
             */
            void retrieveInputTextHost(const sf::Event& event);

            /**
             * @brief Retrieve the input text for the port
             *
             * @param event The event to retrieve
             * @author Adam Lesage
             */
            void retrieveInputTextPort(const sf::Event& event);

            /**
             * @brief Retrieve the input game selection
             *
             * Choices are "R-Type" and "Platformer"
             *
             * @param event The event to retrieve
             * @author Adam Lesage
             */
            void retrieveInputGameSelection(const sf::Event& event);

            /**
             * @brief Get the Host object
             *
             * @return std::string The host
             * @author Adam Lesage
             */
            std::string getHost() const {
                return _inputTextHost.getString();
            }

            /**
             * @brief Get the Server Port object
             *
             * @return unsigned short The server port
             * @author Adam Lesage
             */
            unsigned short getServerPort() const {
                return std::stoi(_inputTextPort.getString().toAnsiString());
            }

            /**
             * @brief Get the Game Selected object
             *
             * @return std::string The game selected
             * @author Adam Lesage
             */
            std::string getGameSelected() const {
                return _gameSelected;
            }

            /**
             * @brief Get the instance of _isOffline
             *
             * @return bool the value of the boolean _isOffline
             * @author Adam Lesage
             */
            bool getOfflineSelection() {
                return _isOffline;
            }

        protected:
        private:
            /**
             * @brief Check if the host and port are valid
             *
             * @return true if the host and port are valid, false otherwise
             * @author Adam Lesage
             */
            bool areHostAndPortValid();

            std::shared_ptr<sf::RenderWindow> _window;
            std::string _inputBoxSelected; // Can be "host" or "port" or "gameSelection"
            std::string _gameSelected;     // Can be "R-Type" or "Platformer"
            bool _invalidPortOrHost;
            bool _isOffline;

            sf::Text _inputTextHost;
            sf::Text _inputTextPort;
            sf::Font _font;
    };
}; // namespace RType

#endif /* !CLIENTCONNEXIONHANDLING_HPP_ */
