/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_

#include "../registry/Registry.hpp"
#include "../components/Charging.hpp"
#include "../components/Color.hpp"
#include "../components/Controllable.hpp"
#include "../components/Damage.hpp"
#include "../components/Direction.hpp"
#include "../components/Drawable.hpp"
#include "../components/Freeze.hpp"
#include "../components/Health.hpp"
#include "../components/Level.hpp"
#include "../components/Position.hpp"
#include "../components/Revivable.hpp"
#include "../components/Rotation.hpp"
#include "../components/Scale.hpp"
#include "../components/Shoot.hpp"
#include "../components/ShootingSpeed.hpp"
#include "../components/Sound.hpp"
#include "../components/Sprite.hpp"
#include "../components/Tag.hpp"
#include "../components/Type.hpp"
#include "../components/Velocity.hpp"
#include "../components/ParentId.hpp"
#include "../../client/Mediator/IMediator.hpp"
#include "../components/Annimation.hpp"
#include <iostream>
#include <memory>
#include <libconfig.h++>

class Systems {
    public:
        /**
         * @brief Update entity's position based on its velocity.
         *
         * @param reg The registry containing the components.
         */
        void position_system(Registry& reg);

        /**
         * @brief Update entity's velocity based on user input.
         *
         * @param reg The registry containing the components.
         * @param window The window to get the input from.
         * @param mediator The mediator to notify the game engine.
         * @param shootSound The function to play the shoot sound.
         */
        void control_system(Registry& reg,
                            sf::RenderWindow& window,
                            std::shared_ptr<RType::IMediator> mediator,
                            std::function<void()> shootSound);

        /**
         * @brief Draw all entities with a position and a drawable component.
         *
         * @param reg The registry containing the components.
         * @param window The window to draw the entities on.
         */
        void draw_system(Registry& reg, sf::RenderWindow& window);

        /**
         * @brief Update the position of all entities based on their velocity.
         *
         * @param reg The registry containing the components.
         */
        void collision_system(Registry& reg, sf::RenderWindow& window);

        /**
         * @brief Update the direction of all entities based on their velocity.
         *
         * @param reg The registry containing the components.
         */
        void direction_system(Registry& reg, libconfig::Config &playerConfig);
        /**
         * @brief Update the annimation of all entity
         *
         * @param reg The registry containing the components.
         */
        void annimation_system(Registry& reg);
};

#endif /* !SYSTEMS_HPP_ */
