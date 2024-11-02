/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RType
*/

#include "RTypeOffline.hpp"

RType::RTypeOffline::RTypeOffline() {
    _camera = std::make_shared<Camera>();
}

RType::RTypeOffline::~RTypeOffline() {
}

void RType::RTypeOffline::handleOfflineGame() {
    bool isPlayerInList                 = false;
    const unsigned short NUMBER_ENEMIES = 8;

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
        entity.size       = {150, 100};
        entity.sprite.spritePath =
            std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_1.png";
        entity.sprite.rectPos  = {263, 0};
        entity.sprite.rectSize = {263, 116};
        entity.direction.x     = 0;
        entity.direction.y     = 0;
        this->_camera->listEntityToDisplay.push_back(entity);
    }

    const float spawnInterval = 1.0f;

    if (this->getEnemyCount() < NUMBER_ENEMIES
        && _enemySpawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
        this->createEnemy();
        _enemySpawnClock.restart();
    }
    this->handleInput();
    this->handleProjectile();
    this->handleEnemies();
    this->makeEnemyShoot();
}

void RType::RTypeOffline::handleProjectile() {
    // Iterate in reverse to avoid indexing issues when removing elements
    for (int i = this->_camera->listEntityToDisplay.size() - 1; i >= 0; i--) {
        if (this->isEntityAProjectile(this->_camera->listEntityToDisplay[i])
            || this->isEntityAnEnemyProjectile(this->_camera->listEntityToDisplay[i])) {
            EntityRenderInfo& projectile = this->_camera->listEntityToDisplay[i];

            // Move projectile
            projectile.position.x += projectile.direction.x;
            projectile.position.y += projectile.direction.y;

            // Check for collision with other entities
            for (int j = 0; (size_t)j < this->_camera->listEntityToDisplay.size(); j++) {
                if (j == i) continue; // Skip self

                EntityRenderInfo& target = this->_camera->listEntityToDisplay[j];

                // Check if the projectile intersects with the target entity
                if (isCollision(projectile, target)) {
                    if (this->isEntityAPlayer(target)
                        && this->isEntityAnEnemyProjectile(projectile) == true) {
                        this->gameOver();
                        return;
                    }

                    // Handle collision (e.g., remove projectile and affect target if it's an enemy)
                    if (this->isEntityAnEnemy(target)
                        && this->isEntityAnEnemyProjectile(projectile) == false) {
                        this->_camera->listEntityToDisplay.erase(this->_camera->listEntityToDisplay.begin()
                                                                 + i);
                        this->_camera->listEntityToDisplay.erase(this->_camera->listEntityToDisplay.begin()
                                                                 + j);
                        break;
                    }
                }
            }

            // Remove the projectile if it is outside the window
            if (projectile.position.x > 1920 || projectile.position.x < 0 || projectile.position.y > 1080
                || projectile.position.y < 0) {
                this->_camera->listEntityToDisplay.erase(this->_camera->listEntityToDisplay.begin() + i);
            }
        }
    }
}

void RType::RTypeOffline::handleCollisions() {
    // Iterate over entities
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        EntityRenderInfo& entityA = this->_camera->listEntityToDisplay[i];

        // Iterate again over entities
        for (size_t j = i + 1; j < this->_camera->listEntityToDisplay.size(); j++) {
            EntityRenderInfo& entityB = this->_camera->listEntityToDisplay[j];

            // Skip if they are the same entity or if neither is a projectile
            if (&entityA == &entityB || (!isEntityAProjectile(entityA) && !isEntityAProjectile(entityB)))
                continue;

            // Check for collision between entityA and entityB
            if (isCollision(entityA, entityB)) {
                if (this->isEntityAPlayer(entityA) || this->isEntityAPlayer(entityB)) {
                    this->gameOver();
                    return;
                }
                // Handle collision logic here (e.g., remove projectiles, apply damage)
                if (isEntityAProjectile(entityA)) {
                    this->_camera->listEntityToDisplay.erase(this->_camera->listEntityToDisplay.begin() + i);
                }
                if (isEntityAProjectile(entityB)) {
                    this->_camera->listEntityToDisplay.erase(this->_camera->listEntityToDisplay.begin() + j);
                }
                break;
            }
        }
    }
}

void RType::RTypeOffline::jump() {
    return;
}

void RType::RTypeOffline::applyGravity() {
    return;
}

void RType::RTypeOffline::handleInput() {
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
            entity.size       = {150, 100};
            entity.sprite.spritePath =
                std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_1.png";
            entity.sprite.rectPos  = {0, 0};
            entity.sprite.rectSize = {100, 100};
            entity.direction.x     = 4;
            entity.direction.y     = 0;
            this->_camera->listEntityToDisplay.push_back(entity);
            _shootClock.restart();
        }
    }

    // Handle direction changes
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
            this->_camera->listEntityToDisplay[i].position.x +=
                this->_camera->listEntityToDisplay[i].direction.x;
            this->_camera->listEntityToDisplay[i].position.y +=
                this->_camera->listEntityToDisplay[i].direction.y;
            this->_camera->listEntityToDisplay[i].direction.x = 0;
            this->_camera->listEntityToDisplay[i].direction.y = 0;
        }
    }
}

bool RType::RTypeOffline::isEntityAPlayer(EntityRenderInfo currentEntity) const {
    if (currentEntity.sprite.spritePath
            == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_1.png"
        || currentEntity.sprite.spritePath
               == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_2.png"
        || currentEntity.sprite.spritePath
               == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_3.png"
        || currentEntity.sprite.spritePath
               == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_4.png"
        || currentEntity.sprite.spritePath
               == std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_5.png") {
        return true;
    }
    return false;
}

bool RType::RTypeOffline::isEntityAProjectile(EntityRenderInfo currentEntity) const {
    if (currentEntity.sprite.spritePath
        == std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_1.png") {
        return true;
    }
    return false;
}

bool RType::RTypeOffline::isEntityAnEnemy(EntityRenderInfo currentEntity) const {
    if (currentEntity.sprite.spritePath
        == std::string("assets") + PATH_SEPARATOR + "ennemy" + PATH_SEPARATOR + "enemy_2.png") {
        return true;
    }
    return false;
}

bool RType::RTypeOffline::isEntityAnEnemyProjectile(EntityRenderInfo currentEntity) const {
    if (currentEntity.sprite.spritePath
        == std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_2.png") {
        return true;
    }
    return false;
}

EntityRenderInfo RType::RTypeOffline::getPlayerFromCamera() const {
    EntityRenderInfo emptyEntity;

    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->isEntityAPlayer(this->_camera->listEntityToDisplay[i]) == true) {
            return this->_camera->listEntityToDisplay[i];
        }
    }
    return emptyEntity;
}

void RType::RTypeOffline::createEnemy() {
    EntityRenderInfo enemy;
    enemy.position.x = 2000;
    enemy.position.y = 100 + rand() % (1800 - 100 + 1);
    enemy.size       = {150, 100};
    enemy.sprite.spritePath =
        std::string("assets") + PATH_SEPARATOR + "ennemy" + PATH_SEPARATOR + "enemy_2.png";
    enemy.sprite.rectPos  = {0, 0};
    enemy.sprite.rectSize = {33, 36};
    enemy.direction.x     = -2;
    enemy.direction.y     = 0;
    this->_camera->listEntityToDisplay.push_back(enemy);
}

void RType::RTypeOffline::makeEnemyShoot() {
    const float shootInterval = 0.5f;

    if (_enemyShootClock.getElapsedTime().asSeconds() >= shootInterval) {
        // Reset the clock for the next interval check
        _enemyShootClock.restart();

        // Iterate over the enemies in listEntityToDisplay
        for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
            EntityRenderInfo& entity = this->_camera->listEntityToDisplay[i];

            if (this->isEntityAnEnemy(entity) == true) {
                // Generate a random chance (e.g., 20% chance to shoot each time)
                int shootChance = rand() % 100;
                if (shootChance < 20) { // 20% probability
                    this->createEnemyProjectile(entity);
                }
            }
        }
    }
}

void RType::RTypeOffline::handleEnemies() {
    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        EntityRenderInfo& entity = this->_camera->listEntityToDisplay[i];

        if (this->isEntityAnEnemy(entity) == true || this->isEntityAnEnemyProjectile(entity) == true) {
            entity.position.x += entity.direction.x;
            entity.position.y += entity.direction.y;

            if (entity.position.x < 0 || entity.position.y > 1080 || entity.position.y < 0) {

                this->_camera->listEntityToDisplay.erase(this->_camera->listEntityToDisplay.begin() + i);
            }
        }
    }
}

void RType::RTypeOffline::createEnemyProjectile(EntityRenderInfo enemyShooter) {
    EntityRenderInfo enemyProjectile;
    enemyProjectile.position.x = enemyShooter.position.x + enemyShooter.size.x / 2;
    enemyProjectile.position.y = enemyShooter.position.y + enemyShooter.size.y / 2;
    enemyProjectile.size       = {150, 100};
    enemyProjectile.sprite.spritePath =
        std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_2.png";
    enemyProjectile.sprite.rectPos  = {0, 0};
    enemyProjectile.sprite.rectSize = {100, 100};
    enemyProjectile.direction.x     = -3;
    enemyProjectile.direction.y     = 0;
    this->_camera->listEntityToDisplay.push_back(enemyProjectile);
}

size_t RType::RTypeOffline::getEnemyCount() const {
    size_t enemyCount = 0;

    for (size_t i = 0; i < this->_camera->listEntityToDisplay.size(); i++) {
        if (this->isEntityAnEnemy(this->_camera->listEntityToDisplay[i]) == true) {
            enemyCount++;
        }
    }
    return enemyCount;
}

bool RType::RTypeOffline::isCollision(const EntityRenderInfo& a, const EntityRenderInfo& b) {
    sf::FloatRect rectA(a.position.x, a.position.y, a.size.x, a.size.y);
    sf::FloatRect rectB(b.position.x, b.position.y, b.size.x, b.size.y);
    return rectA.intersects(rectB);
}
