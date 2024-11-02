/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RType
*/

#ifndef RTYPEOFFLINE_HPP_
#define RTYPEOFFLINE_HPP_

#include <iostream>
#include <memory>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "AGame.hpp"

namespace RType {
    /**
     * @brief RTypeOffline class is the logic loaded from client for offline mode gameplay
     * @author Adam Lesage
     */
    class RTypeOffline : public AGame {
        public:
            RTypeOffline();
            ~RTypeOffline();

            /**
             * @brief handle offline game, meaning there is no communication with the server
             *
             * Everything is calculated on the client side
             * @author Adam Lesage
             */
            void handleOfflineGame() override;

            /**
             * @brief jump function
             * @author Adam Lesage
             */
            void jump() override;

            /**
             * @brief apply gravity to the player
             * @author Adam Lesage
             */
            void applyGravity() override;

            /**
             * @brief handle input, can be input from keyboard or mouse
             * @author Adam Lesage
             */
            void handleInput() override;

            /**
             * @brief Manage projectile, move their positions according to their directions
             * @author Adam Lesage
             */
            void handleProjectile();

            /**
             * @brief Check if entity given has sprite of player
             *
             * @param currentEntity Entity to check if it is a player
             * @return True if entity is a player otherwise false if entity is something else than a player
             * @author Adam Lesage
             */
            bool isEntityAPlayer(EntityRenderInfo currentEntity) const;

            /**
             * @brief Check if entity given has sprite of projectile
             *
             * @param currentEntity Entity to check if it is a projectile
             * @return True if entity is a projectile otherwise false if entity is something else than a
             * projectile
             * @author Adam Lesage
             */
            bool isEntityAProjectile(EntityRenderInfo currentEntity) const;

            /**
             * @brief Check if entity given has sprite of enemy projectile
             *
             * @param currentEntity Entity to check if it is an enemy projectile
             * @return True if entity is an enemy projectile otherwise false if entity is something else than
             * a enemy projectile
             * @author Adam Lesage
             */
            bool isEntityAnEnemyProjectile(EntityRenderInfo currentEntity) const;

            /**
             * @brief Check if entity given has sprite of enemy
             *
             * @param currentEntity Entity to check if it is an enemy
             * @return True if entity is an enemy otherwise false if entity is something else than
             * a enemy
             * @author Adam Lesage
             */
            bool isEntityAnEnemy(EntityRenderInfo currentEntity) const;

            /**
             * @brief create an enemy entity
             *
             * @return void
             * @author Adam Lesage
             */
            void createEnemy();

            /**
             * @brief Handle position of enemies and enemy projectiles
             *
             * @return void
             * @author Adam Lesage
             */
            void handleEnemies();

            /**
             * @brief Enemy will randomly shoot so player have to avoid missiles
             *
             * @return void
             * @author Adam Lesage
             */
            void makeEnemyShoot();

            /**
             * @brief Create a projectile shot by an enemy
             *
             * @param enemyShooter Entity that create the projectile
             * @return void
             * @author Adam Lesage
             */
            void createEnemyProjectile(EntityRenderInfo enemyShooter);

            /**
             * @brief browse list of entities until player is found
             *
             * @return Current instance of the player in camera
             * @author Adam Lesage
             */
            EntityRenderInfo getPlayerFromCamera() const;

            /**
             * @brief Get number of entities currently alive
             *
             * @return Number of enemies
             * @author Adam Lesage
             */
            size_t getEnemyCount() const;

            /**
             * @brief if an entity take a damage, the entity die
             *
             * @return void
             * @author Adam Lesage
             */
            void handleCollisions();

            /**
             * @brief check if two entities collides
             *
             * @return true if entities collides, otherwise false
             * @author Adam Lesage
             */
            bool isCollision(const EntityRenderInfo& a, const EntityRenderInfo& b);

        protected:
        private:
            sf::Clock _shootClock;
            sf::Clock _enemyShootClock;
            sf::Clock _enemySpawnClock;
    };
} // namespace RType

#endif /* !RTYPEOFFLINE_HPP_ */
