/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderMediator
*/

#include "RenderMediator.hpp"
#include "Menu/Menu.hpp"
#include "RenderingEngine.hpp"

RType::RenderMediator::RenderMediator(std::shared_ptr<Menu> &menu, RType::AEngine *renderingEngine)
{
    _menu = menu;
    _renderingEngine = renderingEngine;

    _menu->setMediator(this);
}

RType::RenderMediator::~RenderMediator()
{
}

void RType::RenderMediator::notify(std::string sender, std::string event)
{
    std::cout << "Notified by " << sender << " with event " << event << std::endl;
    if (sender == "Menu" && event == "play") {
        this->_renderingEngine->_mediator->notify("RenderingEngine", "play");
    }
}