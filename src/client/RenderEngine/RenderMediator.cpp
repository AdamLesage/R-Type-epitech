/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderMediator
*/

#include "RenderMediator.hpp"

RType::RenderMediator::RenderMediator(std::unique_ptr<Menu> &menu, std::shared_ptr<RenderingEngine> renderingEngine)
{
    _menu = std::move(menu);
    _renderingEngine = renderingEngine;
}

RType::RenderMediator::~RenderMediator()
{
}

void RType::RenderMediator::notify(std::string sender, const std::string &event)
{
    (void)sender;
    (void)event;
}