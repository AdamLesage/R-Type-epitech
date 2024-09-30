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

extern "C" RType::GameEngine *entryPointGameEngine()
{
    return (new RType::GameEngine());
}
