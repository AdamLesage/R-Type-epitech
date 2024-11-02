/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** DoodleJump
*/

#ifndef DOODLEJUMPOFFLINE_HPP_
#define DOODLEJUMPOFFLINE_HPP_

#include <iostream>
#include <memory>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "AGame.hpp"

namespace RType {
    /**
     * @brief DoodleJumpOffline class
     *
     * This class is the DoodleJumpOffline game
     *
     * @class DoodleJumpOffline and inherits from AGame
     */
    class DoodleJumpOffline : public AGame {
        public:
            /**
             * @brief Construct a new DoodleJumpOffline object
             */
            DoodleJumpOffline();

            /**
             * @brief Destroy the DoodleJumpOffline object
             */
            ~DoodleJumpOffline();

            /**
             * @brief handle offline game, meaning there is no communication with the server
             *
             * Everything is calculated on the client side
             */
            void handleOfflineGame() override;

            /**
             * @brief jump function
             */
            void jump() override;

            /**
             * @brief apply gravity to the player
             */
            void applyGravity() override;

            /**
             * @brief handle input, can be input from keyboard or mouse
             */
            void handleInput() override;

        protected:
        private:
            float _initialYPosition;
            float _jumpVelocity;
            bool _canJump;
            bool _canApplyGravity;
    };
} // namespace RType

#endif /* !DOODLEJUMPOFFLINE_HPP_ */
