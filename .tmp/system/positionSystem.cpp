/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** loggingSystem
*/

#include "../Registery.hpp"
#include "../components/Velocity.hpp"
#include "../components/Position.hpp"
#include <iostream>

void position_system( Registery & r ) {
    auto &positions = r.get_components<position>();
    auto &velocities = r.get_components<velocity>();
    for ( size_t i = 0; i < positions.size () && i < velocities.size(); ++ i ) {
        auto & pos = positions[i];
        auto & vel = velocities[i];
        if (pos && vel) {
            pos.value()->x += vel.value()->vx;
            pos.value()->y += vel.value()->vy;
        }
    }
}