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
    #include "../../shared/components/Pattern.hpp"
    #include "../GameLogique/NetworkSender.hpp"
    #include <iostream>
    #include <cmath>

class Systems {
    public:
        /**
         * @brief Update entity's position based on its velocity.
         *
         * @param reg The registry containing the components.
         */
        void position_system(Registry &reg, std::unique_ptr<NetworkSender> &network);

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
        void collision_system(Registry &reg, sf::RenderWindow &window);

        /**
         * @brief Update the position of all entities based on their velocity.
         *
         * @param reg The registry containing the components.
         * @param entity_t playedId The id of the player.
         * @param deltaTime The time since the last update.
         * @param shootRequest The request to shoot.
         */
        void shoot_system(Registry &reg, entity_t playerId, float deltaTime, bool shootRequest);
    
        /**
         * @brief Update the position for a wave patten
         *
         * @param reg The registry containing the components.
         * @param totalTime The count since the start.
         */
        void wave_pattern_system(Registry &reg, float totalTime);
};

#endif /* !SYSTEMS_HPP_ */
