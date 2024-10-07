/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderingEngine
*/

#include "RenderingEngine.hpp"

RType::RenderingEngine::RenderingEngine()
{
    std::cout << "Rendering Engine created" << std::endl;
    _menu = std::make_shared<Menu>();
    std::cout << "Menu created" << std::endl;
    _renderMediator = std::make_shared<RenderMediator>(_menu, nullptr);
    std::cout << "RenderMediator created" << std::endl;
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
