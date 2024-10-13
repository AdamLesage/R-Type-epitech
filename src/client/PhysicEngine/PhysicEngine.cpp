/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** PhysicEngine
*/

#include "PhysicEngine.hpp"

RType::PhysicEngine::PhysicEngine() {
}

RType::PhysicEngine::~PhysicEngine() {
}

void RType::PhysicEngine::run() {
}

void RType::PhysicEngine::setMediator(std::shared_ptr<IMediator> mediator) {
    _mediator = mediator;
}

extern "C" RType::PhysicEngine* entryPointPhysicEngine() {
    return (new RType::PhysicEngine());
}
