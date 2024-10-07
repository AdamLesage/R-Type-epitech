/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AEngine
*/

#include "AEngine.hpp"

RType::AEngine::AEngine(std::shared_ptr<IMediator> mediator = nullptr)
{
    _mediator = mediator;
}

RType::AEngine::~AEngine()
{
}

void RType::AEngine::setMediator(std::shared_ptr<IMediator> mediator)
{
    std::cout << "setMediator" << std::endl;
    // _mediator = mediator;
}

void RType::AEngine::run()
{
}
