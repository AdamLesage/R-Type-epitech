/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** controlSystem
*/

#include "../Registery.hpp"
#include "../Components/velocity.hpp"
#include "../Components/position.hpp"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

void control_system(Registery& r) {
    auto& positions = r.get_components<position>();
    auto& velocities = r.get_components<velocity>();
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto& pos = positions[i];
        auto& vel = velocities[i];
        if (pos && vel) {
            // Get keyboard inputs
            bool leftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            bool rightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
            bool upKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            bool downKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

            // Update velocity based on inputs
            if (leftKeyPressed) {
                vel.value()->vx = -1;
            } else if (rightKeyPressed) {
                vel.value()->vx = 1;
            } else {
                vel.value()->vx = 0;
            }

            if (upKeyPressed) {
                vel.value()->vy = -1;
            } else if (downKeyPressed) {
                vel.value()->vy = 1;
            } else {
                vel.value()->vy = 0;
            }

            // Update position based on velocity
            pos.value()->x += vel.value()->vx;
            pos.value()->y += vel.value()->vy;
        }
    }
}