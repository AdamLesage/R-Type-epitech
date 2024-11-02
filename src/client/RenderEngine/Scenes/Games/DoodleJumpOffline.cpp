/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** DoodleJumpOffline
*/

#include "DoodleJumpOffline.hpp"

RType::DoodleJumpOffline::DoodleJumpOffline()
{
    _camera = std::make_shared<Camera>();
    _isJumping = false;
    _canJump = true;
    _canApplyGravity = false;
}

RType::DoodleJumpOffline::~DoodleJumpOffline()
{
}

void RType::DoodleJumpOffline::handleOfflineGame()
{
    bool isPlayerInList = false;
    const size_t NUMBER_PLATFORM = 25;

    // Create player if not in the list
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {
            isPlayerInList = true;
        }
    }
    if (!isPlayerInList) {
        EntityRenderInfo entity;
        entity.position.x = 1920 / 2;
        entity.position.y = 1080 / 2;
        entity.size = {100, 100};
        entity.sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png";
        entity.sprite.rectPos = {0, 0};
        entity.sprite.rectSize = {100, 100};
        entity.direction.x = 0;
        entity.direction.y = 0;
        this->_camera->listEntityToDisplay.push_back(entity);
    }

    // Need to set the camera to display the entities
    if (this->_camera->listEntityToDisplay.size() < NUMBER_PLATFORM) {
        for (size_t i = this->_camera->listEntityToDisplay.size(); i < NUMBER_PLATFORM; i++) {
            EntityRenderInfo entity;
            entity.position.x = rand() % 1920;
            entity.position.y = rand() % 1080;
            entity.size = {100, 100};
            entity.sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png";
            entity.sprite.rectPos = {0, 0};
            entity.sprite.rectSize = {100, 100};
            entity.direction.x = 0;
            entity.direction.y = 0.2;
            _initialYPosition = entity.position.y;

            this->_camera->listEntityToDisplay.push_back(entity);
        }
    }

    // Move entities
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        this->_camera->listEntityToDisplay[i].position.y += this->_camera->listEntityToDisplay[i].direction.y;
        this->_camera->listEntityToDisplay[i].position.x += this->_camera->listEntityToDisplay[i].direction.x;

        if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {
            if (this->_camera->listEntityToDisplay[i].direction.x > 0) {
                this->_camera->listEntityToDisplay[i].sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png";
            } else if (this->_camera->listEntityToDisplay[i].direction.x < 0) {
                this->_camera->listEntityToDisplay[i].sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png";
            } else {
                this->_camera->listEntityToDisplay[i].sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png";
            }

            if (this->_camera->listEntityToDisplay[i].position.y > 1080 + 1080 / 2) { // Game over because player fell
                this->gameOver(); 
            }
        }
        if (this->_camera->listEntityToDisplay[i].position.y > 1080 &&
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png") {
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
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {
            if (this->_camera->listEntityToDisplay[i].position.y < 1080 / 2) {
                this->_camera->listEntityToDisplay[i].direction.y += 1;
            } else {
                this->_camera->listEntityToDisplay[i].direction.y = 0;
            }
        }
    }
    this->handleInput();
    this->applyGravity();
}

void RType::DoodleJumpOffline::applyGravity()
{
    const float GRAVITY = 2.0f;

    float jumpImpulseVel = -2.0f; 
    float jumpAccel = -1.0f;

    if (_isJumping) {
        for (auto& player : this->_camera->listEntityToDisplay) {
            if (player.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
                player.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
                player.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {
                for (auto& platform : this->_camera->listEntityToDisplay) {
                    if (platform.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png" && player.position.y < 100) {
                        platform.direction.y = GRAVITY * 2; // Increase speed of platforms because player is jumping on top of the screen
                    } else if (platform.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png" && player.position.y < 500) {
                        platform.direction.y = GRAVITY; // Increase speed of platforms because player is jumping on top of the screen
                    } else if (platform.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png" && player.position.y >= 500) {
                        platform.direction.y = 1.0f;
                    }
                }
            }
        }
    } else {
        for (auto& platform : this->_camera->listEntityToDisplay) {
            if (platform.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png") {
                platform.direction.y = 0.2f;
            }
        }
    }

    if (_startOfJump + std::chrono::milliseconds(500) < std::chrono::system_clock::now()) {
        _isJumping = false;
        _canJump = true;
    }

    for (auto &entity : this->_camera->listEntityToDisplay) {
        if (entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
            entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {

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

            // Handle collision with platforms
            for (auto &platform : this->_camera->listEntityToDisplay) {
                if (platform.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "green-tile.png") {
                    // If player collides with the top of the platform
                    if (entity.position.y + entity.size.y >= platform.position.y &&
                        entity.position.y + entity.size.y <= platform.position.y + platform.size.y &&
                        entity.position.x + entity.size.x > platform.position.x &&
                        entity.position.x < platform.position.x + platform.size.x) {
                        // entity.position.y = platform.position.y - entity.size.y;
                        this->jump();
                    }
                }
            }
        }
    }
}

void RType::DoodleJumpOffline::jump()
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
            entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
            entity.sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {
            entity.direction.y = _jumpVelocity;  // Impulsion initiale du saut
        }
    }
}

void RType::DoodleJumpOffline::handleInput()
{
    // Handle key pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
                this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
                this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {
                this->_camera->listEntityToDisplay[i].sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png";
                this->_camera->listEntityToDisplay[i].direction.x = 1;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
                this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
                this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {
                this->_camera->listEntityToDisplay[i].sprite.spritePath = std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png";
                this->_camera->listEntityToDisplay[i].direction.x = -1;
            }
        }
    }

    // Move player based on the distance between the player and the mouse position
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    float maxSpeed = 5.0f;
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-left.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-right.png" ||
            this->_camera->listEntityToDisplay[i].sprite.spritePath == std::string("assets") + PATH_SEPARATOR + "doodle_jump" + PATH_SEPARATOR + "lik-front.png") {
            
            float playerX = this->_camera->listEntityToDisplay[i].position.x;
            float distance = mousePosition.x - playerX;
            float direction = (distance > 0) ? 1.0f : -1.0f;
            float speed = std::min(maxSpeed, std::abs(distance) / 10.0f); // Adjust the divisor to control sensitivity

            this->_camera->listEntityToDisplay[i].direction.x = direction * speed;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->_canApplyGravity = true;
        this->jump();
    }
}