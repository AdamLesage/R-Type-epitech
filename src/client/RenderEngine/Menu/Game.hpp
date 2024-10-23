/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../GameMetrics/GameMetrics.hpp"
#include "../../../shared/entities/Entity.hpp"
#include "../../../shared/registry/Registry.hpp"
#include "../../../shared/systems/Systems.hpp"
#include "../../Mediator/IMediator.hpp"
#include "../../GameMetrics/GameMetrics.hpp"
#include "Settings.hpp"
#include "Toolbar.hpp"
#include "../../Camera.hpp"
#include <mutex>
#include <libconfig.h++>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace RType {
    class Game {
        public:
            /**
             * @brief Default constructor.
             */
            Game() {
                window            = nullptr;
                currentFrame      = 1;
                frameDuration     = 0.05f;
                animationComplete = false;
            }

            /**
             * @brief Construct a new Game object.
             *
             * @param _window The window to display the game on.
             */
            Game(std::shared_ptr<sf::RenderWindow> _window);

            /**
             * @brief Destroy the Game object.
             */
            ~Game();

            /**
             * @brief Displays the subtitle of a shoot.
             */

            void displayPiou();

            /**
             * @brief Plays the shoot sound.
             */

            void ShootSound();

            /**
             * @brief Displays the cinematic just before the game starts.
             */
            void displayGame(float& latency);

            /**
             * @brief Displays the game we are playing.
             */
            void play(float& latency);
            /**
             * @brief Set the camera to display
             *
             * @param camera the camera to set
             */
            void setCamera(std::shared_ptr<Camera> camera);
            /**
             * @brief set the textures needed from camera to the textures map
             */
            void set_texture();
            /**
             * @brief Convert structure Size to a Vector2f
             */
            sf::Vector2f convertToVector2f(const Size& size);
            /**
             * @brief Convert structure Position to a Vector2f
             */
            sf::Vector2f convertToVector2fb(const Position& pos);

            /**
             * @brief Displays the skip intro text.
             */

            void DisplaySkipIntro();

            /**
             * @brief Sets the mediator, it will be used to communicate with the rendering engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator);
            /**
             * @brief Set the mutex
             *
             * @param mutex the mutex to set
             */
            void setMutex(std::shared_ptr<std::mutex> mutex);
            std::shared_ptr<IMediator>
                _mediator; // Public attribute to be able to access it from the derived class.
        private:
            std::shared_ptr<sf::RenderWindow> window;
            GameMetrics metrics;
            Toolbar toolbar;
            int currentFrame;
            float frameDuration;
            sf::Clock BackgroundClock;
            bool animationComplete;
            /**
             * @brief Handles the events of the game.
             *
             * This function processes events such as closing the window.
             */
            void handleEvents();

            /**
             * @brief Loads the texture of the current frame.
             *
             * @param texture The texture to load.
             * @param sprite The sprite to load.
             * @return true If the texture was loaded successfully.
             * @return false If the texture failed to load.
             */
            bool loadFrameTexture(sf::Texture& texture, sf::RectangleShape& shape);
            Registry _registry;
            Systems _systems;
            std::shared_ptr<Settings> settings;
            std::vector<sf::RectangleShape> backgrounds;
            std::vector<sf::Texture> backgroundTextures;
            std::vector<sf::RectangleShape> players;
            std::vector<sf::RectangleShape> entity;
            std::vector<sf::Texture> playerTextures;
            std::shared_ptr<Camera> _camera;
            /**
             * @brief map that will stock the textures, It will allow us to not load a texture every time we
             * find a new entity but just when we find one that is not in our map
             */
            std::unordered_map<std::string, sf::Texture*> Textures;
            sf::SoundBuffer game_launch_sound;
            sf::Sound game_launch_music;
            sf::SoundBuffer shoot_sound;
            sf::Sound shoot_music;
            sf::SoundBuffer shoot_sound2;
            sf::Sound shoot_music2;
            bool isShooting;
            sf::Font font;
            std::shared_ptr<std::mutex> _mutex;
            bool piou = false;
    };
} // namespace RType

#endif // GAME_HPP
