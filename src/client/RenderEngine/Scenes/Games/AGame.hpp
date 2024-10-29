/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AGame
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "IGame.hpp"

#include <cmath>
#include <chrono>
#include <thread>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace RType {
    /**
     * @brief AGame Abstract class for all games
     */
    class AGame : public IGame {
        public:
            /**
             * @brief Construct a new AGame object
             */
            AGame();

            /**
             * @brief Destroy the AGame object
             */
            ~AGame();

            /**
             * @brief Returns the current instance of the camera
             * 
             * @return std::shared_ptr<Camera> the camera
             */
            std::shared_ptr<Camera> getCamera() const override { return _camera; }

            /**
             * @brief jump function
             */
            void jump() override = 0;

            /**
             * @brief apply gravity to the player
             */
            void applyGravity() override = 0;

            /**
             * @brief handle input, can be input from keyboard or mouse
             */
            virtual void handleInput() override = 0;

        protected:
            std::shared_ptr<Camera> _camera;

            /**
             * @brief The start of the jump
             * 
             * Jump will last 1 second with a curve of 1/2
             */
            std::chrono::time_point<std::chrono::system_clock> _startOfJump;

            /**
             * @brief Boolean to know if the player is jumping
             * 
             * True if the player is jumping else false
             */
            bool _isJumping;
        private:
    };
}

#endif /* !AGAME_HPP_ */
