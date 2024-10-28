/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** DoodleJump
*/

#include "DoodleJump.hpp"

RType::DoodleJump::DoodleJump()
{
    _camera = std::make_shared<Camera>();
}

RType::DoodleJump::~DoodleJump()
{
}

void RType::DoodleJump::handleOfflineGame()
{
    bool isPlayerInList = false;
    // Create player if not in the list
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png") {
            isPlayerInList = true;
        }
    }
    if (!isPlayerInList) {
        EntityRenderInfo entity;
        entity.position.x = 1920 / 2;
        entity.position.y = 1080 / 2;
        entity.size = {100, 100};
        entity.sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png";
        entity.sprite.rectPos = {0, 0};
        entity.sprite.rectSize = {100, 100};
        entity.direction.x = 0;
        entity.direction.y = 0;
        this->_camera->listEntityToDisplay.push_back(entity);
    }

    // Need to set the camera to display the entities
    if (this->_camera->listEntityToDisplay.size() < 15) {
        for (size_t i = this->_camera->listEntityToDisplay.size(); i < 10; i++) {
            EntityRenderInfo entity;
            entity.position.x = rand() % 1920;
            entity.position.y = rand() % 1080;
            entity.size = {100, 100};
            entity.sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png";
            entity.sprite.rectPos = {0, 0};
            entity.sprite.rectSize = {100, 100};
            entity.direction.x = 0;
            entity.direction.y = 1;
            this->_camera->listEntityToDisplay.push_back(entity);
        }
    }

    // Move entities
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        this->_camera->listEntityToDisplay[i].position.y += this->_camera->listEntityToDisplay[i].direction.y;
        this->_camera->listEntityToDisplay[i].position.x += this->_camera->listEntityToDisplay[i].direction.x;

        if (this->_camera->listEntityToDisplay[i].position.y > 1080) {
            this->_camera->listEntityToDisplay[i].position.y = rand() % 401 - 400;
        }

        if (this->_camera->listEntityToDisplay[i].position.x > 1920) {
            this->_camera->listEntityToDisplay[i].position.x = 0;
        }
        if (this->_camera->listEntityToDisplay[i].position.x < 0) {
            this->_camera->listEntityToDisplay[i].position.x = 1920;
        }
    }

    // Apply gravity to player
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png") {
            if (this->_camera->listEntityToDisplay[i].position.y < 1080 / 2) {
                this->_camera->listEntityToDisplay[i].direction.y += 1;
            } else {
                this->_camera->listEntityToDisplay[i].direction.y = 0;
            }

            if (this->_camera->listEntityToDisplay[i].position.y > 1080 / 2) {
                this->_camera->listEntityToDisplay[i].position.y = 1080 / 2;
            }
        }
    }

    // Handle key pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
                this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png") {
                this->_camera->listEntityToDisplay[i].sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png";
                this->_camera->listEntityToDisplay[i].direction.x = 1;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
                this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png") {
                this->_camera->listEntityToDisplay[i].sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png";
                this->_camera->listEntityToDisplay[i].direction.x = -1;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
                this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png") {
                this->_camera->listEntityToDisplay[i].direction.y = -1;
            }
        }
    }
}