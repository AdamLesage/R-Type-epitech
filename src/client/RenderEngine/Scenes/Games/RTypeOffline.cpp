/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RType
*/

#include "RTypeOffline.hpp"

RType::RTypeOffline::RTypeOffline()
{
}

RType::RTypeOffline::~RTypeOffline()
{
}

void RType::RTypeOffline::handleOfflineGame()
{
    bool isPlayerInList = false;

    // Create player if not in the list
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
            isPlayerInList = true;
        }
    }
    // If player is not created, create it
    if (isPlayerInList == false) {
        EntityRenderInfo entity;
        entity.position.x = 50;
        entity.position.y = 50;
        entity.size = {100, 100};
        entity.sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_1.png";
        entity.sprite.rectPos = {0, 0};
        entity.sprite.rectSize = {100, 100};
        entity.direction.x = 0;
        entity.direction.y = 0;
        this->_camera->listEntityToDisplay.push_back(entity);
    }
}

void RType::RTypeOffline::jump()
{
    return;
}

void RType::RTypeOffline::applyGravity()
{
    return;
}

void RType::RTypeOffline::handleInput()
{
    return;
}

bool RType::RTypeOffline::isEntityAPlayer(EntityRenderInfo currentEntity) const
{
    if (currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_1.png" ||
        currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_2.png" ||
        currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_3.png" ||
        currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_4.png" ||
        currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_5.png") {
        return true;
    }
    return false;
}
