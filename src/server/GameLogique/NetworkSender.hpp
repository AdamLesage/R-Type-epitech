/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkSender
*/

#ifndef NetworkSender_HPP_
#define NetworkSender_HPP_

#include <memory>
#include "../network/Server.hpp"

class NetworkSender {
    public:
        NetworkSender(std::shared_ptr<NetworkLib::Server> network);
        ~NetworkSender();

        /**
         * @brief Sends the creation of a player to all clients.
         *
         * @param id The unique identifier of the created player.
         * @param pos_x The x-coordinate of the player's initial position.
         * @param pos_y The y-coordinate of the player's initial position.
         */
        void sendCreatePlayer(int id, float pos_x, float pos_y);

        /**
         * @brief Sends the creation of an enemy to all clients.
         *
         * @param type The type or class of the created enemy.
         * @param id The unique identifier of the created enemy.
         * @param pos_x The x-coordinate of the enemy's initial position.
         * @param pos_y The y-coordinate of the enemy's initial position.
         */
        void sendCreateEnemy(char type, int id, float pos_x, float pos_y);

        /**
         * @brief Sends the creation of a wall entity to all clients.
         *
         * @param id The unique identifier of the created wall.
         * @param pos_x The x-coordinate of the wall's position.
         * @param pos_y The y-coordinate of the wall's position.
         * @param size_x The width of the wall.
         * @param size_y The height of the wall.
         */
        void sendCreateWall(int id, float pos_x, float pos_y, float size_x, float size_y);

        /**
         * @brief Sends the creation of a projectile to all clients.
         *
         * @param id The unique identifier of the created projectile.
         * @param pos_x The x-coordinate of the projectile's position.
         * @param pos_y The y-coordinate of the projectile's position.
         * @param parent_id The identifier of the entity that created or shot the projectile.
         */
        void sendCreateProjectil(int id, float pos_x, float pos_y, int parent_id);

        /**
         * @brief Sends the creation of a reward (e.g., collectible) to all clients.
         *
         * @param id The unique identifier of the created reward.
         * @param pos_x The x-coordinate of the reward's position.
         * @param pos_y The y-coordinate of the reward's position.
         */
        void sendCreateReward(int id, float pos_x, float pos_y);

        /**
         * @brief Sends the creation of a bonus or power-up to all clients.
         *
         * @param type The type or class of the created Bonus.
         * @param id The unique identifier of the created bonus.
         * @param pos_x The x-coordinate of the bonus's position.
         * @param pos_y The y-coordinate of the bonus's position.
         */
        void sendCreateBonus(char type, int id, float pos_x, float pos_y);

        /**
         * @brief Sends a delete command for an entity to all clients.
         *
         * @param id The unique identifier of the entity to be deleted.
         */
        void sendDeleteEntity(int id);

        /**
         * @brief Sends an update on the position of an entity to all clients.
         *
         * @param id The unique identifier of the entity whose position is being updated.
         * @param pos_x The new x-coordinate of the entity's position.
         * @param pos_y The new y-coordinate of the entity's position.
         */
        void sendPositionUpdate(int id, float pos_x, float pos_y);

        /**
         * @brief Sends a health update for an entity to all clients.
         *
         * @param id The unique identifier of the entity whose health is being updated.
         * @param hp The updated health points of the entity.
         */
        void sendHealthUpdate(int id, int hp);

        /**
         * @brief Sends information about a projectile collision with another entity to all clients.
         *
         * @param id_projectil The unique identifier of the projectile involved in the collision.
         * @param id_entity The unique identifier of the entity hit by the projectile.
         */
        void sendProjectilColision(int id_projectil, int id_entity);

    private:
        std::shared_ptr<NetworkLib::Server> _network;
};

#endif /* !NetworkSender_HPP_ */
