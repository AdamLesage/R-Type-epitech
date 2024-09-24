/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkEngine
*/

#include "NetworkEngine.hpp"

NetworkEngine::NetworkEngine()
{
}

NetworkEngine::~NetworkEngine()
{
}

void NetworkEngine::doSomething()
{
    std::cout << "NetworkEngine" << std::endl;
    this->_mediator->notify("NetworkEngine", "doSomething");
}
