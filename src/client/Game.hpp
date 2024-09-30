#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class Game {
public:
    Game() {
        window = nullptr;
        currentFrame = 1;
        frameDuration = 0.05f;
        animationComplete = false;
    }
    explicit Game(std::shared_ptr<sf::RenderWindow> window);

    ~Game();

    void displayGame();

    sf::Text gameInProgressText;

private:
    std::shared_ptr<sf::RenderWindow> window;
    sf::Font font;
    int currentFrame;
    float frameDuration;
    bool animationComplete;
    void handleEvents();
    bool loadFrameTexture(sf::Texture& texture, sf::Sprite& sprite);
};

#endif // GAME_HPP
