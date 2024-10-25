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
    class Menu : public ARenderEngineScene  {
        public:
            /**
             * @brief Construct a new Menu object.
             *
             * @param _window The window to display the menu on.
             */
            Menu(std::shared_ptr<sf::RenderWindow> wdw);

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
            void runScene() override;

        private:
            int selectedOption; // The selected option
            sf::Font font; // The font used for the menu
            sf::Text menuOptions[3]; // Play, Settings, Quit
            sf::Texture logoTexture; // The texture of the logo
            sf::Sprite logoSprite; // The sprite of the logo
            sf::SoundBuffer selectBuffer; // The buffer of the select sound
            sf::Sound selectSound; // The sound played when selecting an option
            std::shared_ptr<sf::RenderWindow> window; // The window to display the menu on
            sf::RectangleShape background; // The background of the menu
            sf::Texture backgroundTexture; // The texture of the background
            std::shared_ptr<Settings> settings; // The settings of the menu
            std::shared_ptr<Lobby> lobby; // The lobby of the menu
            sf::SoundBuffer backgroundBuffer; // The buffer of the background music
            sf::Sound backgroundMusic; // The background music
            sf::RenderTexture RenderTexture; // The render texture
            sf::Shader colorblindShader[5]; // The colorblind shader (Deuteranopia, Protanopia, Tritanopia, Achromatopsia, Normal)
            // std::shared_ptr<Game> games;
    };
} // namespace RType

#endif /* !MENU_HPP_ */
