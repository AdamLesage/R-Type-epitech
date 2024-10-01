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
    #include "../../shared/components/Shoot.hpp"
    #include "../GameLogique/NetworkSender.hpp"
    #include "../utils/Logger.hpp"
    #include <iostream>
    #include <cmath>

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
        void control_system(Registry &reg, RType::Logger &logger);

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
         * @brief Update the position of all entities based on their velocity.
         *
         * @param reg The registry containing the components.
         */
        void collision_system(Registry &reg, sf::RenderWindow &window, RType::Logger &logger);

        /**
         * @brief Update the position of all entities based on their velocity.
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
         * @brief Update the position of all entities based on their velocity.
         *
         * @param reg The registry containing the components.
         */
        void death_system(Registry &reg, RType::Logger &logger);
};

#endif /* !SYSTEMS_HPP_ */
