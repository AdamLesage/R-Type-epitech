/*
** EPITECH PROJECT, 2024
** *
** File description:
** AGame
*/

#include "AGame.hpp"

RType::AGame::AGame()
{
    _isJumping = false;
}

RType::AGame::~AGame()
{
}

void RType::AGame::jump()
{
    std::cout << "Jumping" << std::endl;
}

void RType::AGame::applyGravity()
{
    std::cout << "Applying gravity" << std::endl;
}
