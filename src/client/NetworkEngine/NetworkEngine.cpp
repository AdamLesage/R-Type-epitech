/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkEngine
*/

#include "NetworkEngine.hpp"

RType::NetworkEngine::NetworkEngine()
{
}

RType::NetworkEngine::NetworkEngine(std::string host, unsigned short server_port, unsigned short local_port)
{
    _client = std::make_unique<NetworkLib::Client>(host, server_port, local_port);
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

    try {
        std::string message = _client->popMessage();
        // Call the mediator to send the message to the game engine
        this->_mediator->notify("NetworkEngine", message);
    } catch (const std::logic_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void RType::NetworkEngine::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
}

extern "C" RType::NetworkEngine *entryPointNetworkEngine()
{
    return (new RType::NetworkEngine());
}
