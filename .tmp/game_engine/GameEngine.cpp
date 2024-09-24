/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameEngine
*/

#include "GameEngine.hpp"

GameEngine::GameEngine()
{
    // This constructor will initialize all the components of the game engine, initialize all the systems, and initialize the registry.
    _registery = Registery();
}

GameEngine::~GameEngine()
{
}
