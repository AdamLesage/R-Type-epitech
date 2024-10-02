#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../../shared/entities/Entity.hpp"
#include "../../../shared/registry/Registry.hpp"
#include "../../../shared/systems/Systems.hpp"
#include "Settings.hpp"

namespace RType {
    class Game {
    public:

        /**
         * @brief Default constructor.
         */
        Game() {
            window = nullptr;
            currentFrame = 1;
            frameDuration = 0.05f;
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
         * @brief Displays the cinematic just before the game starts.
         */
        void displayGame();

        /**
         * @brief Displays the game we are playing.
         */
        void play();
    private:
        std::shared_ptr<sf::RenderWindow> window;
        sf::Font font;
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
        bool loadFrameTexture(sf::Texture& texture, sf::Sprite& sprite);
        Registry _registry;
        Systems _systems;
        std::shared_ptr<Settings> settings;
        std::vector<sf::RectangleShape> backgrounds;
        std::vector<sf::Texture> backgroundTextures;
        std::vector<sf::RectangleShape> players;
        std::vector<sf::Texture> playerTextures;
    };
}

#endif // GAME_HPP
