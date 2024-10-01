#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../../shared/entities/Entity.hpp"
#include "../../../shared/registry/Registry.hpp"
#include "../../../shared/systems/Systems.hpp"

namespace RType {
    class Game {
    public:
        Game() {
            window = nullptr;
            currentFrame = 1;
            frameDuration = 0.05f;
            animationComplete = false;
        }
        explicit Game(std::shared_ptr<sf::RenderWindow> _window);

        ~Game();

        void displayGame();
        void play();
        sf::Text gameInProgressText;

    private:
        std::shared_ptr<sf::RenderWindow> window;
        sf::Font font;
        int currentFrame;
        float frameDuration;
        bool animationComplete;
        void handleEvents();
        bool loadFrameTexture(sf::Texture& texture, sf::Sprite& sprite);
        Registry _registry;
        Systems _systems;
        std::vector<sf::RectangleShape> backgrounds;
        std::vector<sf::Texture> backgroundTextures;
        sf::RectangleShape player;
        std::vector<sf::Texture> playerTextures;
    };
}

#endif // GAME_HPP
