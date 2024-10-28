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

void RType::DoodleJump::jump()
{
    // Si le joueur est déjà en train de sauter, on ne fait rien
    if (_canJump == false)
        return;

    // Initialiser le saut
    _isJumping = true;
    _canJump = false;           // Empêche les sauts supplémentaires pendant le saut actuel
    _jumpVelocity = -10;        // Vélocité initiale du saut ajustée pour un saut plus réaliste
    _startOfJump = std::chrono::system_clock::now();

    // Appliquer l'impulsion de saut au joueur
    for (auto &entity : this->_camera->listEntityToDisplay) {
        if (entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png") {
            entity.direction.y = _jumpVelocity;  // Impulsion initiale du saut
        }
    }
}

void RType::DoodleJump::applyGravity()
{
    std::cout << "Player position: " << this->_camera->listEntityToDisplay[0].position.y << std::endl;

    if (_canApplyGravity == false)
        return;

    for (auto &entity : this->_camera->listEntityToDisplay) {
        if (entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png") {

            // Appliquer la gravité si le joueur est en train de sauter ou de tomber
            if (_isJumping) {
                entity.direction.y += 1; // Effet de gravité
                if (entity.direction.y >= 0) {
                    _isJumping = false;   // Terminer le saut quand la vélocité devient positive
                    _canJump = true;      // Permettre de sauter de nouveau quand le saut se termine
                }
            } else {
                // Appliquer la gravité normale lorsque le joueur est en l'air après un saut
                entity.direction.y += 1;
                if (entity.position.y >= _initialYPosition) { // Si le joueur atteint ou dépasse la position de départ
                    entity.position.y = _initialYPosition;
                    entity.direction.y = 0;
                    _canJump = true;      // Permettre un nouveau saut
                }
            }
        }
    }
}
