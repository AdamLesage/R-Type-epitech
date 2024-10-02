/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
    #define SYSTEMS_HPP_

    #include "../../shared/registry/Registry.hpp"
    #include "../../shared/components/Controllable.hpp"
    #include "../../shared/components/Drawable.hpp"
    #include "../../shared/components/Position.hpp"
    #include "../../shared/components/Velocity.hpp"
    #include "../../shared/components/Type.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../../shared/components/Damage.hpp"
    #include "../../shared/components/ShootingSpeed.hpp"
    #include "../../shared/components/Wave_Pattern.hpp"
    #include "../../shared/components/StraightPattern.hpp"
    #include "../../shared/components/Shoot.hpp"
    #include "../../shared/components/Direction.hpp"
    #include "../GameLogique/NetworkSender.hpp"
    #include "../../shared/components/Size.hpp"
    #include "../utils/Logger.hpp"
    #include <iostream>
    #include <cmath>
    #include <chrono>

class Systems {
    public:
        /**
         * @brief Update entity's position based on its velocity.
         *
         * @param reg The registry containing the components.
         * @param network The class for sending data to client
         */
        void position_system(Registry &reg, std::unique_ptr<NetworkSender> &network, RType::Logger &logger);

        /**
         * @brief Update entity's velocity based on user input.
         *
         * @param reg The registry containing the components.
         * @param window The window to get the input from.
         */
        void control_system(Registry &reg, bool up, bool down, bool left, bool right, RType::Logger &logger);

        /**
         * @brief Draw all entities with a position and a drawable component.
         *
         * @param reg The registry containing the components.
         * @param window The window to draw the entities on.
         */
        void draw_system(Registry &reg, sf::RenderWindow &window, RType::Logger &logger);

        /**
         * @brief Log the position and velocity of all entities.
         *
         * @param reg The registry containing the components.
         * @param positions The sparse array containing the positions.
         * @param velocities The sparse array containing the velocities.
         */
        void logging_system(SparseArray<Position_s> const &positions, SparseArray<Velocity_s> const &velocities, RType::Logger &logger);

        /**
         * @briefHandle the collisions between entities.
         *
         * @param reg The registry containing the components.
         */
        void collision_system(Registry &reg, std::pair<size_t, size_t> MapSize, RType::Logger &logger);

        /**
         * @brief Handles the shoot for the entities.
         *
         * @param reg The registry containing the components.
         * @param playerId playedId The id of the player.
         * @param network The class for sending data to client
         */
        void shoot_system(Registry &reg, entity_t playerId, std::unique_ptr<NetworkSender> &networkSender, RType::Logger &logger);

        /**
         * @brief Update the position for a wave patten
         *
         * @param reg The registry containing the components.
         * @param totalTime The count since the start.
         */
        void wave_pattern_system(Registry &reg, float totalTime, RType::Logger &logger);
        /**
         * @brief Update the health of all entities based on the damages / regeneration / healing they receive.
         *
         * @param reg The registry containing the components.
         */
        void health_system(Registry &reg);

        /**
         * @brief Handle the death of entities
         *
         * @param reg The registry containing the components.
         */
        void death_system(Registry &reg, RType::Logger &logger);

    private:
        /**
         * @brief Check if an entity is colliding with the borders of the map.
         *
         * @param reg The registry containing the components.
         * @param entityId The id of the entity to check.
         * @param position The position of the entity.
         * @param size The size of the entity.
         * @param type The type of the entity.
         * @param MapSize The size of the map.
         * @return void
         */
        void check_borders_collisions(Registry &reg, size_t entityId, Position_s *position, Size_s *size,
            Type_s *type, std::pair<size_t, size_t> MapSize, RType::Logger &logger);


        /**
         * @brief Check if 2 entities are colliding.
         *
         * @param reg The registry containing the components.
         * @param entityId1 The id of the first entity.
         * @param position1 The position of the first entity.
         * @param size1 The size of the first entity.
         * @param entityId2 The id of the second entity.
         * @param position2 The position of the second entity.
         * @param size2 The size of the second entity.
         */
        void check_entities_collisions(Registry &reg, size_t entityId1, Position_s *position1, Size_s *size1,
            size_t entityId2, Position_s *position2, Size_s *size2, RType::Logger &logger);

        /**
         * @brief Update the movement for a straight ligne pattern
         *
         * @param reg The registry containing the components.
         */
        void Straight_line_pattern_system(Registry &reg);
};

#endif /* !SYSTEMS_HPP_ */