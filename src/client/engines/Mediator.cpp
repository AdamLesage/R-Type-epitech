/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Mediator
*/

#include "Mediator.hpp"

Mediator::Mediator(std::shared_ptr<GameEngine> gameEngine, std::shared_ptr<NetworkLib::NetworkEngine> networkEngine, std::shared_ptr<RenderingEngine> renderingEngine)
{
    this->_gameEngine = gameEngine;
    this->_networkEngine = networkEngine;
    this->_renderingEngine = renderingEngine;
}

Mediator::~Mediator()
{
}

void Mediator::notifyGameEngine(std::string sender, std::string event)
{
    if (sender != "GameEngine")
        return;
}

void Mediator::notifyNetworkEngine(std::string sender, std::string event)
{
    if (sender != "NetworkEngine")
        return;

    // if (event == "newConnection") // example of event
    //     this->_gameEngine->createPlayer();
}

void Mediator::notifyRenderingEngine(std::string sender, std::string event)
{
    if (sender != "RenderingEngine")
        return;
}

void Mediator::notify(std::string sender, std::string event)
{
    this->notifyGameEngine(sender, event);
    this->notifyNetworkEngine(sender, event);
    this->notifyRenderingEngine(sender, event);
}