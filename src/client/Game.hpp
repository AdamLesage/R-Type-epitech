#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class Game {
public:
    explicit Game(std::shared_ptr<sf::RenderWindow> window);

    ~Game();

    void displayGame();

private:
    std::shared_ptr<sf::RenderWindow> window;
    sf::Font font;
    sf::Text gameInProgressText;
    int currentFrame;
    float frameDuration;
    bool animationComplete;
    void handleEvents();
    bool loadFrameTexture(sf::Texture& texture, sf::Sprite& sprite);
};

#endif // GAME_HPP
