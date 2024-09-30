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
    std::cout << "NetworkEngine" << std::endl;
    this->_mediator->notify("NetworkEngine", "run");
}

void RType::NetworkEngine::updateData()
{
    std::cout << "NetworkEngine updateData" << std::endl;
}

extern "C" RType::NetworkEngine *entryPointNetworkEngine()
{
    return (new RType::NetworkEngine());
}
