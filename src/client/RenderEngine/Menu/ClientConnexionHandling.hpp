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
     */
    class ClientConnexionHandling {
        public:
            /**
             * @brief Construct a new Client Connexion Handling object
             */
            ClientConnexionHandling(std::string host = "", unsigned short server_port = 0);

            /**
             * @brief Destroy the Client Connexion Handling object
             */
            ~ClientConnexionHandling();

            /**
             * @brief Display the connexion window
             */
            void displayConnexionWindow();

            /**
             * @brief Display the background
             */
            void displayBackground();

            /**
             * @brief Display the input text for the host
             */
            void displayInputTextHost(sf::Text labelHost, sf::Text labelPort);

            /**
             * @brief Display the input text for the port
             */
            void displayInputTextPort(sf::Text labelPort, sf::Text labelHost);

            /**
             * @brief Display the submit button
             */
            void displaySubmitButton();

            /**
             * @brief Display the error message if the host or port are invalid
             */
            void displayError();

            /**
             * @brief Retrieve the input text for the host
             */
            void retrieveInputTextHost(const sf::Event& event);

            /**
             * @brief Retrieve the input text for the port
             */
            void retrieveInputTextPort(const sf::Event& event);

            /**
             * @brief Get the Host object
             *
             * @return std::string The host
             */
            std::string getHost() const {
                return _inputTextHost.getString();
            }

            /**
             * @brief Get the Server Port object
             *
             * @return unsigned short The server port
             */
            unsigned short getServerPort() const {
                return std::stoi(_inputTextPort.getString().toAnsiString());
            }

        protected:
        private:
            /**
             * @brief Check if the host and port are valid
             *
             * @return true if the host and port are valid, false otherwise
             */
            bool areHostAndPortValid();

            std::shared_ptr<sf::RenderWindow> _window;
            std::string _inputBoxSelected; // Can be "host" or "port"
            bool _invalidPortOrHost;

            sf::Text _inputTextHost;
            sf::Text _inputTextPort;
            sf::Font _font;
            bool _isHostSelected = false;
            bool _isPortSelected = false;
    };
}; // namespace RType

#endif /* !CLIENTCONNEXIONHANDLING_HPP_ */
