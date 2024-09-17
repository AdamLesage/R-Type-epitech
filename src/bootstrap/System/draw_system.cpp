/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** draw_system
*/

#include "../Registery.hpp"
#include "../Components/velocity.hpp"
#include "../Components/position.hpp"
#include "../Components/drawable.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"

void draw_system(Registery & r, std::shared_ptr<sf::RenderWindow> window)
{
    auto const &positions = r.get_components<position>();
    auto const &drawables = r.get_components<drawable>();
    for ( size_t i = 0; i < positions.size () && i < drawables.size(); ++ i ) {
        auto const & pos = positions[i];
        auto const & draw = drawables[i];
        if (pos && draw) {
            sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(100, 100));
            rect.setPosition(pos.value()->x, pos.value()->y);
            rect.setFillColor(sf::Color::Blue);
            window->draw(rect);
        }
    }
}
