/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkEngine
*/

#include "NetworkEngine.hpp"

RType::NetworkEngine::NetworkEngine()
{
    _client = std::make_unique<NetworkLib::Client>("127.0.0.0", 50000, 50010);
}

RType::NetworkEngine::~NetworkEngine()
{
}


void RType::NetworkEngine::run()
{
}

void RType::NetworkEngine::updateData()
{
    if (_client->hasMessage() == false)
        return;

    std::string message = _client->popMessage();
    // Call the mediator to send the message to the game engine
    this->_mediator->notify("NetworkEngine", message);
}

extern "C" RType::NetworkEngine *entryPointNetworkEngine()
{
    return (new RType::NetworkEngine());
}
