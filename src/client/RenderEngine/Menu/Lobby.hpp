/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Lobby
*/

#ifndef Lobby_HPP_
#define Lobby_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../../../shared/entities/Entity.hpp"
#include "../../../shared/registry/Registry.hpp"
#include "../../../shared/systems/Systems.hpp"
#include "Game.hpp"
#include "Settings.hpp"
#include "../../Mediator/IMediator.hpp"
#include "../../../shared/utils/Logger.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace RType {
    class Lobby {
        public:
            /**
             * @brief Construct a new Lobby object.
             *
             * @param _window The window to display the Lobby on.
             */
            Lobby(std::shared_ptr<sf::RenderWindow> _window);

            /**
             * @brief Destroy the Lobby object.
             */
            ~Lobby();

            /**
             * @brief Moves the selection right.
             */
            void moveRight();

            /**
             * @brief Moves the selection left.
             */
            void moveLeft();

            /**
             * @brief Get the selected option.
             *
             * @return int The selected option.
             */
            int getSelectedOption() const;

            /**
             * @brief Adjusts the volume of the background music.
             *
             * @param increase Whether to increase or decrease the volume.
             */
            void adjustVolume(bool increase);

            /**
             * @brief Handles key press events for volume adjustment.
             *
             * @param event The SFML event to handle.
             */
            void handleKeyPress(const sf::Event& event);

            /**
             * @brief Displays the subtitles of the lobby.
             */
            void displaySubtitles();

            /**
             * @brief Displays the sound of the lobby.
             */
            void displaySound();

            /**
             * @brief Displays the menu.
             */
            void displayLobby();

            /**
             * @brief Sets the mediator, it will be used to communicate with the rendering engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator);
            /**
             * @brief Set the camera to display
             *
             * @param camera the camera to set
             */
            void setCamera(std::shared_ptr<Camera> camera);
            /**
             * @brief Set the mutex
             *
             * @param mutex the mutex to set
             */
            void setMutex(std::shared_ptr<std::mutex> mutex);

            std::shared_ptr<IMediator>
                _mediator; // Public attribute to be able to access it from the derived class.
        protected:
            std::shared_ptr<sf::RenderWindow> window; // The window to display the Lobby on.
            int selectedOption; // The selected option
            sf::Font font; // The font used for the Lobby
            sf::Text playersNames[5]; // The names of the players
            sf::Sound backgroundMusic; // The background music of the Lobby
            sf::SoundBuffer backgroundBuffer; // The buffer of the background music
            sf::Texture backgroundTexture; // The texture of the background
            sf::RectangleShape background; // The background of the Lobby
            sf::Texture logoTexture; // The texture of the logo
            sf::Sprite logoSprite; // The sprite of the logo
            sf::Text menuOptions[3]; // Play, Settings, Quit
            sf::SoundBuffer selectBuffer; // The buffer of the select sound
            sf::Sound selectSound; // The sound played when selecting an option
            std::vector<sf::Texture> playerTextures; // The textures of the players
            std::vector<sf::Sprite> playerSprites; // The sprites of the players
            std::shared_ptr<Camera> _camera; // The camera to display
            Registry _registry; 
            Systems _systems;
            std::shared_ptr<Game> games; //the class game used to display the game
            std::shared_ptr<Settings> settings; //the class settings used to display the settings
            std::shared_ptr<std::mutex> _mutex; 
            sf::RenderTexture RenderTexture; // The render texture
            sf::Shader colorblindShader[5]; // The colorblind shader (Deuteranopia, Protanopia, Tritanopia, Achromatopsia, Normal)

        private:
            Logger _logger;
    };

} // namespace RType

#endif /* !Lobby_HPP_ */
