/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderMediator
*/

#include "RenderMediator.hpp"
#include "Menu/Menu.hpp"
#include "RenderingEngine.hpp"

RType::RenderMediator::RenderMediator(std::shared_ptr<Menu> &menu, RType::IEngine *renderingEngine)
{
    std::cout << "RenderMediator constructor" << std::endl;
    _menu = menu;
    _renderingEngine = renderingEngine;

    _menu->setMediator(this);
}

RType::RenderMediator::~RenderMediator()
{
}

void RType::RenderMediator::notify(std::string sender, std::string event)
{
    (void)sender;
    (void)event;
    if (sender == "Menu" && event == "play") {
        std::cout << "Play received from menu" << std::endl;
    }
}