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
}

RType::GameEngine::~GameEngine()
{
}

void RType::GameEngine::run()
{
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
