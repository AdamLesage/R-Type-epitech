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

namespace RType
{
    class Lobby
    {
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
        void handleKeyPress(const sf::Event &event);


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

        std::shared_ptr<IMediator> _mediator; // Public attribute to be able to access it from the derived class.
    protected:
        int selectedOption;
        std::shared_ptr<sf::RenderWindow> window;
        sf::Font font;
        sf::Text playersNames[5];
        sf::Sound backgroundMusic;
        sf::SoundBuffer backgroundBuffer;
        sf::Texture backgroundTexture;
        sf::RectangleShape background;
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::Text menuOptions[3]; // Play, Settings, Quit
        sf::SoundBuffer selectBuffer;
        sf::Sound selectSound;
        std::vector<sf::Texture> playerTextures;
        std::vector<sf::Sprite> playerSprites;
        std::shared_ptr<Camera> _camera;
        Registry _registry;
        Systems _systems;
        std::shared_ptr<Game> games;
        std::shared_ptr<Settings> settings;
        std::shared_ptr<std::mutex> _mutex;
    private:
    };

}

#endif /* !Lobby_HPP_ */
