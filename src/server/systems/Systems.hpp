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
    #include "../../shared/components/Score.hpp"
    #include "../../shared/components/PlayerName.hpp"
    #include <iostream>
    #include <algorithm>
    #include <fstream>
    #include <libconfig.h++>

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
         * @brief Handle the save of the score of the player.
         * @param reg
         */
        void score_system(Registry &reg);

    private:
        /**
         * @brief Read the file that contains the scores history
         *
         * @param cfg The libconfig config object
         * @param configPath The path to the file
         * @return true The file was read successfully
         * @return false An error occurred while reading the file
         */
        bool read_scores_file(libconfig::Config &cfg, const std::string &configPath);

        /**
         * @brief Handle the update of the scores history, fetch the kast 10 scores and insert the new one
         *
         * @param cfg The libconfig config object
         * @param playerNames The names of the players
         * @param totalScore The total score of the players (sum of all players)
         */
        void update_scores(libconfig::Config &cfg, const std::string &playerNames, size_t totalScore);

        /**
         * @brief Save the scores history to the file
         *
         * @param cfg The libconfig config object
         * @param configPath The path to the file
         * @return true The file was written successfully
         * @return false An error occurred while writing the file
         */
        bool write_to_scores_file(libconfig::Config &cfg, const std::string &configPath);
};

#endif /* !SYSTEMS_HPP_ */
