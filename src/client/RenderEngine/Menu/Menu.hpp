/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Lobby.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace RType {
    class IMediator;
    class Menu {
        public:
            /**
             * @brief Construct a new Menu object.
             *
             * @param _window The window to display the menu on.
             */
            Menu(std::shared_ptr<sf::RenderWindow> wdw, std::shared_ptr<RType::IMediator> _mediator);

            /**
             * @brief Destroy the Menu object.
             */
            ~Menu() = default;

            /**
             * @brief Draws the menu.
             */
            void draw();
            /**
             * @brief Moves the selection up.
             */
            void moveUp();
            /**
             * @brief Moves the selection down.
             */
            void moveDown();
            /**
             * @brief Get the selected option.
             *
             * @return int The selected option.
             */
            int getSelectedOption() const;
            /**
             * @brief Handles key press events for volume adjustment.
             *
             * @param event The SFML event to handle.
             */
            void handleKeyPress(const sf::Event& event);

            /**
             * @brief Adjusts the volume of the background music.
             *
             * @param increase Whether to increase or decrease the volume.
             */
            void adjustVolume(bool increase);

            /**
             * @brief Displays the sound of the lobby.
             */
            void displaySound();

            /**
             * @brief Displays the subtitles of the lobby.
             */
            void displaySubtitles();

            /**
             * @brief Displays the menu.
             */
            int displayMenu();

            /**
             * @brief Sets the mediator, it will be used to communicate with the rendering engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<RType::IMediator> mediator);

            std::shared_ptr<IMediator>
                _mediator; // Public attribute to be able to access it from the derived class.
        private:
            int selectedOption;
            sf::Font font;
            sf::Text menuOptions[3]; // Play, Settings, Quit
            sf::Texture logoTexture;
            sf::Sprite logoSprite;
            sf::SoundBuffer selectBuffer;
            sf::Sound selectSound;
            std::shared_ptr<sf::RenderWindow> window;
            sf::RectangleShape background;
            sf::Texture backgroundTexture;
            std::shared_ptr<Settings> settings;
            std::shared_ptr<Lobby> lobby;
            sf::SoundBuffer backgroundBuffer;
            sf::Sound backgroundMusic;
            // std::shared_ptr<Game> games;
    };
} // namespace RType

#endif /* !MENU_HPP_ */
