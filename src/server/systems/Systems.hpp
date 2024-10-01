/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
    #define SYSTEMS_HPP_

    #include "../registry/Registry.hpp"
    #include "../../shared/components/Controllable.hpp"
    #include "../../shared/components/Drawable.hpp"
    #include "../../shared/components/Position.hpp"
    #include "../../shared/components/Velocity.hpp"
    #include "../../shared/components/Type.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../../shared/components/Damage.hpp"
    #include "../../shared/components/ShootingSpeed.hpp"
    #include "../../shared/components/Size.hpp"
    #include <iostream>

class Systems {
    public:
        /**
         * @brief Update entity's position based on its velocity.
         *
         * @param reg The registry containing the components.
         */
        void position_system(Registry &reg);

        /**
         * @brief Update entity's velocity based on user input.
         *
         * @param reg The registry containing the components.
         * @param window The window to get the input from.
         */
        void control_system(Registry &reg);

        /**
         * @brief Draw all entities with a position and a drawable component.
         *
         * @param reg The registry containing the components.
         * @param window The window to draw the entities on.
         */
        void draw_system(Registry &reg, sf::RenderWindow &window);

        /**
         * @brief Log the position and velocity of all entities.
         *
         * @param reg The registry containing the components.
         * @param positions The sparse array containing the positions.
         * @param velocities The sparse array containing the velocities.
         */
        void logging_system(SparseArray<Position_s> const &positions, SparseArray<Velocity_s> const &velocities);

        /**
         * @brief Update the position of all entities based on their velocity.
         *
         * @param reg The registry containing the components.
         */
        void collision_system(Registry &reg, std::pair<size_t, size_t> MapSize);

        /**
         * @brief Update the position of all entities based on their velocity.
         *
         * @param reg The registry containing the components.
         * @param entity_t playedId The id of the player.
         * @param deltaTime The time since the last update.
         * @param shootRequest The request to shoot.
         */
        void shoot_system(Registry &reg, entity_t playerId, float deltaTime, bool shootRequest);

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
            Type_s *type, std::pair<size_t, size_t> MapSize);


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
            size_t entityId2, Position_s *position2, Size_s *size2);
};

#endif /* !SYSTEMS_HPP_ */
