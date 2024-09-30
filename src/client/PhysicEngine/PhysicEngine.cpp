/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** PhysicEngine
*/

#include "PhysicEngine.hpp"

RType::PhysicEngine::PhysicEngine()
{
}

RType::PhysicEngine::~PhysicEngine()
{
}

void RType::PhysicEngine::run()
{
    std::cout << "PhysicEngine is running" << std::endl;
}

extern "C" RType::PhysicEngine *entryPointPhysicEngine()
{
    return (new RType::PhysicEngine());
}
