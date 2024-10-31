/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <libconfig.h++>
#include <string>
#include "../ARenderEngineScene.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace RType {
    class Settings : public ARenderEngineScene {
        public:
            /**
             * @brief Construct a new Settings object.
             *
             * @param _window The window to display the settings on.
             */
            Settings(std::shared_ptr<sf::RenderWindow> _window);

            /**
             * @brief Destroy the Settings object.
             */
            ~Settings();

            /**
             * @brief Displays the settings.
             *
             * @param if the bool is true it means that we are in a game
             */
            void displaySettings(bool ingame);

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
             * @brief Changes the key of the selected option.
             *
             * @param key The new key.
             */
            void changeKey(std::string key);

            /**
             * @brief Initializes the text for menu options and the position of the sprites.
             */

            void initTextAndSprites();

            /**
             * @brief Displays the input of the settings.
             */

            void displayInput();

            /**
             * @brief Executes the scene with the given latency.
             * 
             * This function is responsible for running the scene and handling any
             * necessary updates or rendering based on the provided latency.
             * 
             * @param latency A reference to a float representing the latency to be used
             *                during the scene execution.
             */
            void runScene(float& latency)  override;


            /**
             * @brief Displays the settings.
             */
            void display();
            /**
             * @brief get the value of a key from the cfg file
             *
             * @param cfg libconfig
             * @param key_name name of the key needed
             */
            const std::string get_key_value(libconfig::Config& cfg, const std::string key_name);
            /**
             * @brief get the value of a key from the cfg file
             *
             * @param cfg libconfig
             * @param key_name name of the key to change
             * @param new_value new value for the key
             */
            int set_key_value(libconfig::Config& cfg, const std::string key_name, const std::string new_value);

        protected:
            int selectedOption;                       // The selected option
            sf::Sound selectSound;                    // The sound played when selecting an option
            std::shared_ptr<sf::RenderWindow> window; // The window to display the settings on
            sf::Font font;                            // The font used for the settings
            sf::Text menuOptions[9]; // The options of the settings so the keys up, down, left, right, shoot,
                                     // escape, subtitles, colorblind and friendly fire
            sf::Texture logoTexture; // The texture of the logo
            sf::Sprite logoSprite;   // The sprite of the logo
            sf::Event event;         // The event of the settings
            sf::RectangleShape background;   // The background of the settings
            sf::Texture backgroundTexture;   // The texture of the background
            sf::Texture ShootInputTexture;   // The texture of the shoot input
            sf::Sprite ShootInputSprite;     // The sprite of the shoot input
            sf::Texture arrowTexture[4];     // The texture of the arrows up down left right
            sf::Sprite arrowSprite[4];       // The sprite of the arrows up down left right
            std::string newArrowInput;       // The new input of the arrow
            sf::RenderTexture RenderTexture; // The render texture of the settings
            sf::Shader colorblindShader[5];  // The shaders for the colorblind mode (Deuteranopia, Protanopia,
                                             // Tritanopia, Achromatopsia, Normal)

        private:
    };
} // namespace RType

#endif /* !SETTINGS_HPP_ */