/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameOver
*/

#include <SFML/Graphics.hpp>
#include <memory>

#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_

namespace RType {
    class GameOver {
    public:
        GameOver();
        GameOver(std::shared_ptr<sf::RenderWindow> _window);
        ~GameOver();
        void display();
    protected:
        std::shared_ptr<sf::RenderWindow> window;
        sf::Text game_over;
        sf::Text subtitle;
        sf::RectangleShape filter;
        sf::Font font;
    private:
    };
}

#endif /* !GAMEOVER_HPP_ */
