/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>

class Game
{
public:
    Game(std::shared_ptr<sf::RenderWindow> window);
    
    Game();
    
    ~Game();

    void displayGame();

private:
    std::shared_ptr<sf::RenderWindow> window;
};

#endif /* !GAME_HPP_ */
