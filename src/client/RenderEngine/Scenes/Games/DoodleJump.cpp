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
    _isJumping = false;
    _canJump = true;
    _canApplyGravity = false;
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
            _initialYPosition = entity.position.y;
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
        this->_canApplyGravity = true;
        this->jump();
    }
    this->applyGravity();
}

void RType::DoodleJump::applyGravity()
{
    const float GRAVITY = 2.5f;

    float jumpImpulseVel = -2.0f; 
    float jumpAccel = -1.0f;

    if (_startOfJump + std::chrono::milliseconds(500) < std::chrono::system_clock::now()) {
        _isJumping = false;
        _canJump = true;
    }

    for (auto &entity : this->_camera->listEntityToDisplay) {
        if (entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png") {

            // First jump quickly
            if (_isJumping) {
                if (_startOfJump < std::chrono::system_clock::now() - std::chrono::milliseconds(200)) { // Apply impulse for 200ms
                    entity.direction.y = jumpImpulseVel;
                } else if (_startOfJump < std::chrono::system_clock::now() - std::chrono::milliseconds(100)) { // Apply acceleration for 100ms
                    entity.direction.y = jumpAccel; 
                } else {
                    entity.direction.y = GRAVITY;
                }
            } else {
                entity.direction.y = GRAVITY;
            }

            // // Détection de collision avec une plateforme et rebond seulement quand il tombe
            // if (entity.direction.y > 0) { // Le doodle doit être en train de tomber pour vérifier la collision
            //     for (auto &platform : this->_camera->listEntityToDisplay) {
            //         if (platform.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png") {
            //             if (entity.position.y + entity.size.y >= platform.position.y &&
            //                 entity.position.y <= platform.position.y + platform.size.y &&
            //                 entity.position.x + entity.size.x >= platform.position.x &&
            //                 entity.position.x <= platform.position.x + platform.size.x) {
                            
            //                 // Positionner le doodle au-dessus de la plateforme et appliquer le rebond
            //                 entity.position.y = platform.position.y - entity.size.y;
            //                 entity.direction.y = -entity.direction.y;
            //                 _isJumping = true; // Considérer cela comme un nouveau saut
            //                 break; // Sortir de la boucle dès qu'une collision est détectée
            //             }
            //         }
            //     }
            // }
        }
    }
}

void RType::DoodleJump::jump()
{
    // Empêcher les sauts supplémentaires pendant le saut actuel
    if (!_canJump)
        return;

    // Initialiser le saut
    _isJumping = true;
    _canJump = false;               // Désactiver les sauts multiples
    _jumpVelocity = -50;           // Vitesse initiale du saut
    _startOfJump = std::chrono::system_clock::now();

    // Appliquer l'impulsion de saut au doodle
    for (auto &entity : this->_camera->listEntityToDisplay) {
        if (entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png") {
            entity.direction.y = _jumpVelocity;  // Impulsion initiale du saut
        }
    }
}
