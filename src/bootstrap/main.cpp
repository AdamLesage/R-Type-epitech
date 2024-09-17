/*
** EPITECH PROJECT, 2024
** frefref
** Fie description:
** main
*/

#include "SparseArray.hpp"
#include <iostream>
#include "Registery.hpp"
#include "Components/velocity.hpp"
#include "Components/position.hpp"
#include <unistd.h>

void logging_system( Registery & r );
void position_system( Registery & r );
void control_system( Registery & r );

int main() {
    Registery registery;
    bool is_running = true;

    registery.register_component<position>();
    registery.register_component<velocity>();
    registery.spawn_entity();
    Entity entity = registery.entity_from_index(0);

    position position_test;
    position_test.x = 10;
    position_test.y = 40;
    velocity velocity_test;
    velocity_test.vx = 1;
    velocity_test.vy = 2;
    registery.add_component<position>(entity, std::move(position_test));
    registery.add_component<velocity>(entity, std::move(velocity_test));
    while (is_running) {
        sleep(1);
        logging_system(registery);
        position_system(registery);
        control_system(registery);
    }
}
