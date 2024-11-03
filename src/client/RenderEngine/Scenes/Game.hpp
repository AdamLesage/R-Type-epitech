/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../../shared/entities/Entity.hpp"
#include "../../../shared/registry/Registry.hpp"
#include "../../../shared/systems/Systems.hpp"
#include "../../Mediator/IMediator.hpp"
#include "Settings.hpp"
#include "../../Camera.hpp"
#include "../Console/Console.hpp"
#include <mutex>
#include <libconfig.h++>

#include "Games/DoodleJumpOffline.hpp"
#include "Games/RTypeOffline.hpp"
#include "Games/IGame.hpp"
#include "../ARenderEngineScene.hpp"
#include "../../GameMetrics/Toolbar.hpp"
#include "../../GameMetrics/GameMetrics.hpp"
#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace RType {
    class Game : public ARenderEngineScene {
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
            Game(std::shared_ptr<sf::RenderWindow> _window, std::string scenePath);

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
            void runScene(float& latency) override;

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
             * @brief Set the level to display
             *
             * @param level the new level
             */
            void setLevel(size_t level);

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
             * @brief Set the mutex
             *
             * @param mutex the mutex to set
             */
            void setMutex(std::shared_ptr<std::mutex> mutex);

            /**
             * @brief Handles if colorblind is activated
             */
            void handleColorblind();

            /**
             * @brief Return if the game has a cinematic
             *
             * @return true if the game has a cinematic
             */
            bool haveCinematic();

            /**
             * @brief Set the game selected
             *
             * @param gameSelected the game selected
             */
            void setGameSelected(const std::string& gameSelected) {
                _gameSelected = gameSelected;

                if (_gameSelected == "Platformer") {
                    _currentGame = std::make_shared<DoodleJumpOffline>();
                } else if (_gameSelected == "R-Type") {
                    _currentGame = std::make_shared<RTypeOffline>();
                }
            }

            /**
             * @brief Return current instance of currentGame, will be called by mediator to reset game
             * @return current game instance
             * @author Adam Lesage
             */
            std::shared_ptr<IGame> getCurrentGame() const {
                return _currentGame;
            }

            /**
             * @brief Tell to the game is current selection if online or offline
             *
             * @param isOffline True: Offline game, False: Online game
             * @return void
             * @author Adam Lesage
             */
            void setOfflineMode(bool isOffline) {
                _isGameOffline = isOffline;
            }

            /**
             * @brief Display the score of the player
             * 
             * @param win the window to display the score on
             */
            void displayScore(sf::RenderWindow& win);

        protected:
            bool _isGameOffline;

            /**
             * @brief Display the entities health
             *
             * @param win the window to display the health texts on
             */
            void displayEntitiesHealth(sf::RenderWindow& win);

        private:
            std::unique_ptr<sf::Clock> cinematicsClock;
            std::shared_ptr<sf::RenderWindow> window;
            int currentFrame;
            float frameDuration;
            sf::Clock BackgroundClock;
            bool animationComplete;
            std::string _gameSelected;
            /**
             * @brief Handles the events of the game.
             *
             * This function processes events such as closing the window.
             */
            void handleEvents();

            /**
             * @brief Check if the game is offline
             *
             * @return true if the game is offline
             */
            bool isGameOffline();

            /**
             * @brief Loads the texture of the current frame.
             *
             * @param texture The texture to load.
             * @param sprite The sprite to load.
             * @return true If the texture was loaded successfully.
             * @return false If the texture failed to load.
             */
            bool loadFrameTexture(sf::Texture& texture, sf::RectangleShape& shape);
            /**
             * @brief Loads the Backround for the current level setting
             *
             * @param levelSetting The current level setting
             */
            void loadBackgroundConfig(libconfig::Setting& levelSetting);

            libconfig::Config _cfg; // The config file

            Registry _registry;
            Systems _systems;
            std::shared_ptr<Console> console;
            std::shared_ptr<Settings> settings;          // the class settings used to display the settings
            std::vector<sf::RectangleShape> backgrounds; // The backgrounds of the game
            std::vector<sf::Texture> backgroundTextures; // The textures of the backgrounds
            std::vector<sf::RectangleShape> players;     // The players of the game
            std::vector<sf::RectangleShape> entity;      // The entities of the game
            std::vector<sf::Texture> playerTextures;     // The textures of the players
            std::shared_ptr<Camera> _camera;             // The camera to display
            /**
             * @brief map that will stock the textures, It will allow us to not load a texture every time we
             * find a new entity but just when we find one that is not in our map
             */
            std::unordered_map<std::string, sf::Texture*> Textures; // a map that will stock the textures
            sf::Font font;                                          // The font used for the game
            std::shared_ptr<std::mutex> _mutex;
            bool piou = false; // A boolean to know wd need to display the piou sound
            std::shared_ptr<sf::RenderTexture> RenderTexture; // The render texture
            sf::Shader colorblindShader[5]; // The colorblind shader (Deuteranopia, Protanopia, Tritanopia,
                                            // Achromatopsia, Normal)
            sf::Event event;                // The event of the game
            std::shared_ptr<IGame> _currentGame;
            size_t _level;
            GameMetrics metrics;
            Toolbar toolbar;
    };
} // namespace RType

#endif // GAME_HPP
