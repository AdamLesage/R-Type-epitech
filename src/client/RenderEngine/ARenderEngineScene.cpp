/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ARenderEngineScene
*/

#include "ARenderEngineScene.hpp"

RType::ARenderEngineScene::~ARenderEngineScene() {
}

void RType::ARenderEngineScene::setMediator(std::shared_ptr<RType::IMediator> mediator) {
    _mediator = mediator;
}

void RType::ARenderEngineScene::sendStateChange(int newState) {
    _mediator->notify("RenderingEngine", "StateChange " + std::to_string(newState));
}
