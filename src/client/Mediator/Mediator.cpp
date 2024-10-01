/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Mediator
*/

#include "Mediator.hpp"

RType::Mediator::Mediator(std::shared_ptr<GameEngine> gameEngine, std::shared_ptr<NetworkEngine> networkEngine, std::shared_ptr<RenderingEngine> renderingEngine, std::shared_ptr<PhysicEngine> physicEngine, std::shared_ptr<AudioEngine> audioEngine)

{
    this->_gameEngine = gameEngine;
    this->_networkEngine = networkEngine;
    this->_renderingEngine = renderingEngine;
    this->_physicEngine = physicEngine;
    this->_audioEngine = audioEngine;

    this->_gameEngine->setMediator(std::shared_ptr<IMediator>(this));
    this->_networkEngine->setMediator(std::shared_ptr<IMediator>(this));
    this->_renderingEngine->setMediator(std::shared_ptr<IMediator>(this));
    this->_physicEngine->setMediator(std::shared_ptr<IMediator>(this));
    this->_audioEngine->setMediator(std::shared_ptr<IMediator>(this));
}

RType::Mediator::~Mediator()
{
    this->_gameEngine->setMediator(nullptr);
    this->_networkEngine->setMediator(nullptr);
    this->_renderingEngine->setMediator(nullptr);

    this->_gameEngine = nullptr;
    this->_networkEngine = nullptr;
    this->_renderingEngine = nullptr;
}

void RType::Mediator::notifyGameEngine(std::string sender, std::string event)
{
    if (sender != "GameEngine")
        return;
    if (event == "updateData") {
        this->_networkEngine->updateData();
    }
}

void RType::Mediator::notifyNetworkEngine(std::string sender, std::string event)
{
    (void)event;
    if (sender != "NetworkEngine")
        return;

    // Network engine will only call mediator to update the game engine data
    this->_gameEngine->handleServerData(event);
}

void RType::Mediator::notifyRenderingEngine(std::string sender, std::string event)
{
    (void)event;
    if (sender != "RenderingEngine")
        return;
}

void RType::Mediator::notifyPhysicEngine(std::string sender, std::string event)
{
    (void)event;
    if (sender != "PhysicEngine")
        return;
}

void RType::Mediator::notifyAudioEngine(std::string sender, std::string event)
{
    (void)event;
    if (sender != "AudioEngine")
        return;
}

void RType::Mediator::notify(std::string sender, std::string event)
{
    this->notifyGameEngine(sender, event);
    this->notifyNetworkEngine(sender, event);
    this->notifyRenderingEngine(sender, event);
    this->notifyPhysicEngine(sender, event);
    this->notifyAudioEngine(sender, event);
}