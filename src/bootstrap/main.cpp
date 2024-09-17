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
#include "Components/drawable.hpp"
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void logging_system( Registery & r );
void position_system( Registery & r );
void draw_system(Registery &r);
void control_system( Registery & r );

int main() {
    
    bool is_running = true;
    std::shared_ptr<sf::RenderWindow> window;
    window.reset(new sf::RenderWindow(sf::VideoMode(1800, 1000), "r-type"));
    Registery registery(window);
    registery.register_component<position>();
    registery.register_component<velocity>();
    registery.register_component<drawable>();
    registery.spawn_entity();
    Entity entity = registery.entity_from_index(0);

    position position_test;
    position_test.x = 10;
    position_test.y = 40;
    velocity velocity_test;
    velocity_test.vx = 1;
    velocity_test.vy = 2;
    drawable draw;
    draw.isDrawable = true;
    registery.add_component<position>(entity, std::move(position_test));
    registery.add_component<velocity>(entity, std::move(velocity_test));
    registery.add_component<drawable>(entity, std::move(draw));
    registery.add_system(position_system);
    registery.add_system(control_system);
    registery.add_system(draw_system);
    logging_system(registery);
    while (is_running) {
        usleep(1000);
        window->clear();
        registery.run_systems();
        window->display();
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                return 0;
            }
        }
    }
}
