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
}

void RType::AGame::applyGravity()
{
}

void RType::AGame::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
}

void RType::AGame::gameOver()
{
    if (_mediator == nullptr) return; // Invalid mediator

    _mediator->notify("RenderingEngine", "Game over offline");
}

void RType::AGame::resetGame()
{
    this->_camera->listEntityToDisplay.clear();
}
