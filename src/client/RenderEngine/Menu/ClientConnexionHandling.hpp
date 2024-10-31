/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ClientConnexionHandling
*/

#ifndef CLIENTCONNEXIONHANDLING_HPP_
#define CLIENTCONNEXIONHANDLING_HPP_

    #if defined(_WIN32) || defined(_WIN64)
        #include <windows.h>
        #define LIB_EXTENSION ".dll"
        #define PATH_SEPARATOR "\\"
        #define NOMINMAX
    #else
        #include <dlfcn.h>
        #define LIB_EXTENSION ".so"
        #define PATH_SEPARATOR "/"
    #endif

    #include <algorithm>
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <memory>
    #include <cstring>

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
            void displayInputTextHost();

            /**
             * @brief Display the input text for the port
             */
            void displayInputTextPort();

            /**
             * @brief Display the submit button
             */
            void displaySubmitButton();

            /**
             * @brief Display the error message if the host or port are invalid
             */
            void displayError();

            /**
             * @brief Display the game selection
             * 
             * Choices are "R-Type" and "Platformer"
             */
            void displayGameSelection();

            /**
             * @brief Retrieve the input text for the host
             * 
             * @param event The event to retrieve
             */
            void retrieveInputTextHost(const sf::Event &event);

            /**
             * @brief Retrieve the input text for the port
             * 
             * @param event The event to retrieve
             */
            void retrieveInputTextPort(const sf::Event &event);

            /**
             * @brief Retrieve the input game selection
             * 
             * Choices are "R-Type" and "Platformer"
             * 
             * @param event The event to retrieve
             */
            void retrieveInputGameSelection(const sf::Event &event);

            /**
             * @brief Get the Host object
             * 
             * @return std::string The host
             */
            std::string getHost() const { return _inputTextHost.getString(); }

            /**
             * @brief Get the Server Port object
             * 
             * @return unsigned short The server port
             */
            unsigned short getServerPort() const { return std::stoi(_inputTextPort.getString().toAnsiString()); }

            /**
             * @brief Get the Game Selected object
             * 
             * @return std::string The game selected
             */
            std::string getGameSelected() const { return _gameSelected; }
        protected:
        private:
            /**
             * @brief Check if the host and port are valid
             * 
             * @return true if the host and port are valid, false otherwise
             */
            bool areHostAndPortValid();

            std::shared_ptr<sf::RenderWindow> _window;
            std::string _inputBoxSelected; // Can be "host" or "port" or "gameSelection"
            std::string _gameSelected; // Can be "R-Type" or "Platformer"
            bool _invalidPortOrHost;

            sf::Text _inputTextHost;
            sf::Text _inputTextPort;
            sf::Font _font;
    };
}; // namespace RType

#endif /* !CLIENTCONNEXIONHANDLING_HPP_ */
