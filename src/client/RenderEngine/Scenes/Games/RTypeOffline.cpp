/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RType
*/

#include "RTypeOffline.hpp"

RType::RTypeOffline::RTypeOffline()
{
    _camera = std::make_shared<Camera>();
}

RType::RTypeOffline::~RTypeOffline()
{
}

void RType::RTypeOffline::handleOfflineGame()
{
    bool isPlayerInList = false;

    if (this->_camera == nullptr) {
        std::cerr << "Camera is null" << std::endl;
        return;
    }

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
        entity.size = {150, 100};
        entity.sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_1.png";
        entity.sprite.rectPos = {263, 0};
        entity.sprite.rectSize = {263, 116};
        entity.direction.x = 0;
        entity.direction.y = 0;
        this->_camera->listEntityToDisplay.push_back(entity);
    }
    this->handleInput();
    this->handleProjectile();
}

void RType::RTypeOffline::handleProjectile()
{
    // Iterate in reverse to avoid indexing issues when removing elements
    for (int i = this->_camera->listEntityToDisplay.size() - 1; i >= 0; i--) {
        if (this->isEntityAProjectile(this->_camera->listEntityToDisplay[i])) {
            this->_camera->listEntityToDisplay[i].position.x += this->_camera->listEntityToDisplay[i].direction.x;
            this->_camera->listEntityToDisplay[i].position.y += this->_camera->listEntityToDisplay[i].direction.y;

            // Remove the projectile if it is outside the window
            if (this->_camera->listEntityToDisplay[i].position.x > 1920 ||
                this->_camera->listEntityToDisplay[i].position.x < 0 ||
                this->_camera->listEntityToDisplay[i].position.y > 1080 ||
                this->_camera->listEntityToDisplay[i].position.y < 0) {
                
                this->_camera->listEntityToDisplay.erase(this->_camera->listEntityToDisplay.begin() + i);
            }
        }
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
                this->_camera->listEntityToDisplay[i].direction.y = -2;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
                this->_camera->listEntityToDisplay[i].direction.x = -2;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
                this->_camera->listEntityToDisplay[i].direction.y = 2;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
                this->_camera->listEntityToDisplay[i].direction.x = 2;
            }
        }
    }

    // Create projectile
    const float shootCooldown = 0.25f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        // Check if player can shoot
        if (_shootClock.getElapsedTime().asSeconds() >= shootCooldown) {
            EntityRenderInfo player = this->getPlayerFromCamera();
            EntityRenderInfo entity;
            entity.position.x = player.position.x + player.size.x / 2;
            entity.position.y = player.position.y + player.size.y / 2;
            entity.size = {150, 100};
            entity.sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_1.png";
            entity.sprite.rectPos = {0, 0};
            entity.sprite.rectSize = {100, 100};
            entity.direction.x = 4;
            entity.direction.y = 0;
            this->_camera->listEntityToDisplay.push_back(entity);
            _shootClock.restart();
        }
    }

    // Handle direction changes
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
            this->_camera->listEntityToDisplay[i].position.x += this->_camera->listEntityToDisplay[i].direction.x;
            this->_camera->listEntityToDisplay[i].position.y += this->_camera->listEntityToDisplay[i].direction.y;
            this->_camera->listEntityToDisplay[i].direction.x = 0;
            this->_camera->listEntityToDisplay[i].direction.y = 0;
        }
    }
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

bool RType::RTypeOffline::isEntityAProjectile(EntityRenderInfo currentEntity) const
{
    if (currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_1.png" ||
        currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_2.png" ||
        currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_3.png" ||
        currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_4.png" ||
        currentEntity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_5.png") {
        return true;
    }
    return false;
}

EntityRenderInfo RType::RTypeOffline::getPlayerFromCamera() const
{
    EntityRenderInfo emptyEntity;

    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
            return this->_camera->listEntityToDisplay[i];
        }
    }
    return emptyEntity;
}
