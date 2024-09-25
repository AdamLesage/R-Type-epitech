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

RType::NetworkEngine::~NetworkEngine()
{
}

void RType::NetworkEngine::doSomething()
{
    std::cout << "NetworkEngine" << std::endl;
    // this->_mediator->notify("NetworkEngine", "doSomething");
}

void RType::NetworkEngine::run()
{
    std::cout << "NetworkEngine" << std::endl;
    this->_mediator->notify("NetworkEngine", "run");
}

extern "C" RType::NetworkEngine *entryPointNetworkEngine()
{
    return (new RType::NetworkEngine());
}
