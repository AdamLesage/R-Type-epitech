/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** main
*/

#include <iostream>
#include "../shared/entities/Entity.hpp"
#include "registry/Registry.hpp"
#include "systems/Systems.hpp"
#include "sparse_array/SparseArray.hpp"

int main()
{
    Registry reg;
    Systems sys;

    reg.register_component<Position_s>();
    reg.register_component<Velocity_s>();
    reg.register_component<Drawable_s>();
    reg.register_component<Controllable_s>();

    sf::RenderWindow window(sf::VideoMode(1280, 720), "BS-R-TYPE");

    entity_t movable = reg.spawn_entity();
    reg.add_component<Position_s>(movable, Position_s{100.f, 100.f});
    reg.add_component<Velocity_s>(movable, Velocity_s{0.f, 0.f});
    reg.add_component<Drawable_s>(movable, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    reg.get_components<Drawable_s>()[movable]->shape.setFillColor(sf::Color::Blue);
    reg.add_component<Controllable_s>(movable, Controllable_s{});

    entity_t static_entity = reg.spawn_entity();
    reg.add_component<Position_s>(static_entity, Position_s{100.f, 300.f});
    reg.add_component<Drawable_s>(static_entity, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    reg.get_components<Drawable_s>()[static_entity]->shape.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sys.control_system(reg);
        sys.position_system(reg);
        sys.collision_system(reg, window);

        window.clear();
        sys.draw_system(reg, window);
        sys.logging_system(reg.get_components<Position_s>(), reg.get_components<Velocity_s>());
        window.display();
    }
    return 0;
}
