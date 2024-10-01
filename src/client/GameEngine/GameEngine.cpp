/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameEngine
*/

#include "GameEngine.hpp"

RType::GameEngine::GameEngine()
{
    // Register all components
    _registry.register_component<Camera_s>();
    _registry.register_component<Charging_s>();
    _registry.register_component<Color_s>();
    _registry.register_component<Controllable_s>();
    _registry.register_component<Damage_s>();
    _registry.register_component<Drawable_s>();
    _registry.register_component<Freeze_s>();
    _registry.register_component<Health_s>();
    _registry.register_component<Level_s>();
    _registry.register_component<Position_s>();
    _registry.register_component<Revivable_s>();
    _registry.register_component<Rotation_s>();
    _registry.register_component<Scale_s>();
    _registry.register_component<Shoot_s>();
    _registry.register_component<ShootingSpeed_s>();
    _registry.register_component<Sound_s>();
    _registry.register_component<Sprite_s>();
    _registry.register_component<Tag_s>();
    _registry.register_component<Type_s>();
    _registry.register_component<Velocity_s>();

    _protocolParsing = std::make_unique<RType::ProtocolParsing>("./src/client/GameEngine/protocol_config.cfg", _registry);
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
        this->send("updateData"); // Check each frame if there is new data from the server to update the game
        _systems.draw_system(_registry, _window);
        _systems.logging_system(_registry.get_components<Position_s>(), _registry.get_components<Velocity_s>());
        _window.display();
    }
}

void RType::GameEngine::send(const std::string &message)
{
    _mediator->notify("GameEngine", message);
}


void RType::GameEngine::handleServerData(std::string &message)
{
    // To tests this function, notify mediator from NetworkEngine with a message which is binary data
    _protocolParsing->parseData(message.c_str());
}

extern "C" RType::GameEngine *entryPointGameEngine()
{
    return (new RType::GameEngine());
}
