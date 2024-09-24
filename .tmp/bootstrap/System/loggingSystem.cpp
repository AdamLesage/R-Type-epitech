/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** loggingSystem
*/

#include "../Registery.hpp"
#include "../Components/velocity.hpp"
#include "../Components/position.hpp"
#include <iostream>

void logging_system( Registery & r ) {
    auto const &positions = r.get_components<position>();
    auto const &velocities = r.get_components<velocity>();
    for ( size_t i = 0; i < positions.size () && i < velocities.size(); ++ i ) {
        auto const & pos = positions[i];
        auto const & vel = velocities[i];
        if (pos && vel) {
            std::cout << i << " : Position = { " << pos.value()->x << " , " << pos.value()->y << " } , Velocity = { " << vel.value()->vx << " , " << vel.value()->vy << " } " << std::endl;
        }
    }
}