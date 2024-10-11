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
#include "../../shared/components/Score.hpp"
#include "../../shared/components/Wave_Pattern.hpp"
#include "../../shared/components/StraightPattern.hpp"
#include "../../shared/components/PlayerFollowingPattern.hpp"
#include "../../shared/components/ShootPlayerPattern.hpp"
#include "../../shared/components/ShootStraightPattern.hpp"
#include "../../shared/components/Shoot.hpp"
#include "../../shared/components/Direction.hpp"
#include "../GameLogique/NetworkSender.hpp"
#include "../../shared/components/Size.hpp"
#include "../../shared/components/Tag.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <libconfig.h++>
#include "../../shared/utils/Logger.hpp"
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
        void position_system(Registry& reg, std::unique_ptr<NetworkSender>& network, RType::Logger& logger);

        /**
         * @brief Update entity's velocity based on user input.
         *
         * @param reg The registry containing the components.
         * @param window The window to get the input from.
         */
        void control_system(Registry& reg, bool up, bool down, bool left, bool right, RType::Logger& logger);

        /**
         * @brief Draw all entities with a position and a drawable component.
         *
         * @param reg The registry containing the components.
         * @param window The window to draw the entities on.
         */
        void draw_system(Registry& reg, sf::RenderWindow& window, RType::Logger& logger);

        /**
         * @brief Log the position and velocity of all entities.
         *
         * @param reg The registry containing the components.
         * @param positions The sparse array containing the positions.
         * @param velocities The sparse array containing the velocities.
         */
        void logging_system(SparseArray<Position_s> const& positions,
                            SparseArray<Velocity_s> const& velocities,
                            RType::Logger& logger);

        /**
         * @briefHandle the collisions between entities.
         *
         * @param reg The registry containing the components.
         */
        void collision_system(Registry& reg,
                              std::pair<size_t, size_t> MapSize,
                              std::unique_ptr<NetworkSender>& networkSender,
                              RType::Logger& logger);

        /**
         * @brief Handles the shoot for the entities.
         *
         * @param reg The registry containing the components.
         * @param playerId playedId The id of the player.
         * @param network The class for sending data to client
         * @param logger The logger to log the events
         */
        void shoot_system(Registry& reg,
                          entity_t playerId,
                          std::unique_ptr<NetworkSender>& networkSender,
                          RType::Logger& logger);

        /**
         * @brief Handle the save of the score of the player.
         * @param reg
         */
        void score_system(Registry& reg);

        /**
         * @brief Update the position for a wave patten
         *
         * @param reg The registry containing the components.
         * @param totalTime The count since the start.
         */
        void wave_pattern_system(Registry& reg, float totalTime, RType::Logger& logger);

        /**
         * @brief Update the health of all entities based on the damages / regeneration / healing they
         * receive.
         *
         * @param reg The registry containing the components.
         */
        void health_system(Registry& reg);

        /**
         * @brief Handle the death of entities
         *
         * @param reg The registry containing the components.
         */
        void death_system(Registry& reg, RType::Logger& logger);
        /**
         * @brief Update the movement for a straight ligne pattern
         *
         * @param reg The registry containing the components.
         */
        void Straight_line_pattern_system(Registry& reg);
        /**
         * @brief Update the movement based on the closest player
         *
         * @param reg The registry containing the components.
         */
        void player_following_pattern_system(Registry& reg);
        /**
         * @brief Fire an projectill every x seconds
         *
         * @param reg The registry containing the components.
         * @param network The class for sending data to client
         *
         */
        void shoot_straight_pattern_system(Registry& reg, std::unique_ptr<NetworkSender>& networkSender);
        /**
         * @brief Fire an projectill every x seconds to the player
         *
         * @param reg The registry containing the components.
         * @param network The class for sending data to client
         *
         */
        void shoot_player_pattern_system(Registry& reg, std::unique_ptr<NetworkSender>& networkSender);

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
        void check_borders_collisions(Registry& reg,
                                      size_t entityId,
                                      Position_s* position,
                                      Size_s* size,
                                      Type_s* type,
                                      std::pair<size_t, size_t> MapSize,
                                      RType::Logger& logger,
                                      std::unique_ptr<NetworkSender>& networkSender);

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
         * @param logger The logger to log the events.
         * @param networkSender The class for sending.
         * @param entityType1 The type of the first entity.
         * @param entityType2 The type of the second entity.
         */
        void check_entities_collisions(Registry& reg,
                                       size_t entityId1,
                                       Position_s* position1,
                                       Size_s* size1,
                                       size_t entityId2,
                                       Position_s* position2,
                                       Size_s* size2,
                                       RType::Logger& logger,
                                       std::unique_ptr<NetworkSender>& networkSender,
                                       Type_s* entityType1,
                                       Type_s* entityType2);

        /**
         * @brief Read the file that contains the scores history
         *
         * @param cfg The libconfig config object
         * @param configPath The path to the file
         * @return true The file was read successfully
         * @return false An error occurred while reading the file
         */
        bool read_scores_file(libconfig::Config& cfg, const std::string& configPath);

        /**
         * @brief Handle the update of the scores history, fetch the kast 10 scores and insert the new one
         *
         * @param cfg The libconfig config object
         * @param playerNames The names of the players
         * @param totalScore The total score of the players (sum of all players)
         */
        void update_scores(libconfig::Config& cfg, const std::string& playerNames, size_t totalScore);

        /**
         * @brief Save the scores history to the file
         *
         * @param cfg The libconfig config object
         * @param configPath The path to the file
         * @return true The file was written successfully
         * @return false An error occurred while writing the file
         */
        bool write_to_scores_file(libconfig::Config& cfg, const std::string& configPath);

        /**
         * @brief find the pos of the closest player
         *
         * @param reg The registry containing the components.
         * @param position_entity the position of the entity
         * @return return the pos of the closest player
         */
        std::array<float, 2> find_closest_player(Registry& reg, Position* position_entity);
};

#endif /* !SYSTEMS_HPP_ */