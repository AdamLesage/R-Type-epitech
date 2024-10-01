/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameEngine
*/

#include "GameEngine.hpp"

RType::GameEngine::GameEngine()
{
    _registry.register_component<Position_s>();
    _registry.register_component<Velocity_s>();
    _registry.register_component<Drawable_s>();
    _registry.register_component<Controllable_s>();
    _window.create(sf::VideoMode(1280, 720), "R-TYPE");
}

RType::GameEngine::~GameEngine()
{
}

void RType::GameEngine::run()
{
    entity_t movable = _registry.spawn_entity();
    _registry.add_component<Position_s>(movable, Position_s{100.f, 100.f});
    _registry.add_component<Velocity_s>(movable, Velocity_s{0.f, 0.f});
    _registry.add_component<Drawable_s>(movable, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    _registry.get_components<Drawable_s>()[movable]->shape.setFillColor(sf::Color::Blue);
    _registry.add_component<Controllable_s>(movable, Controllable_s{});

    entity_t static_entity = _registry.spawn_entity();
    _registry.add_component<Position_s>(static_entity, Position_s{100.f, 300.f});
    _registry.add_component<Drawable_s>(static_entity, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    _registry.get_components<Drawable_s>()[static_entity]->shape.setFillColor(sf::Color::Red);

    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        _systems.control_system(_registry);
        _systems.position_system(_registry);
        _systems.collision_system(_registry, _window);

        _window.clear();
        // this->send("updateData");
        _systems.draw_system(_registry, _window);
        _systems.logging_system(_registry.get_components<Position_s>(), _registry.get_components<Velocity_s>());
        _window.display();
    }
}

void RType::GameEngine::send(const std::string &message)
{
    _mediator->notify("GameEngine", message);
}

extern "C" RType::GameEngine *entryPointGameEngine()
{
    return (new RType::GameEngine());
}
