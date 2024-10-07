/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderMediator
*/

#include "RenderMediator.hpp"
#include "Menu/Menu.hpp"

RType::RenderMediator::RenderMediator(std::shared_ptr<Menu> &menu, std::shared_ptr<RenderingEngine> renderingEngine)
{
    std::cout << "RenderMediator constructor" << std::endl;
    // _menu = std::move(menu);
    // _renderingEngine = renderingEngine;

    // _menu->setMediator(std::shared_ptr<RenderMediator>(this));
}

RType::RenderMediator::~RenderMediator()
{
}

void RType::RenderMediator::notify(std::string sender, std::string event)
{
    (void)sender;
    (void)event;
}