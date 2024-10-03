/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderingEngine
*/

#include "RenderingEngine.hpp"

RType::RenderingEngine::RenderingEngine()
{
    _menu = std::make_unique<Menu>();
}

RType::RenderingEngine::~RenderingEngine()
{
}

void RType::RenderingEngine::run()
{
    _menu->displayMenu();
}

void RType::RenderingEngine::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
}

extern "C" RType::RenderingEngine *entryPointRenderingEngine()
{
    return (new RType::RenderingEngine());
}
