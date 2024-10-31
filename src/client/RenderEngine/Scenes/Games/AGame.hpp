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
    * 
    * @author Adam Lesage
     */
    class AGame : public IGame {
        public:
            /**
             * @brief Construct a new AGame object
             * 
             * @author Adam Lesage
             */
            AGame();

            /**
             * @brief Destroy the AGame object
             * 
             * @author Adam Lesage
             */
            ~AGame();

            /**
             * @brief Returns the current instance of the camera
             * 
             * @return std::shared_ptr<Camera> the camera
             * @author Adam Lesage
             */
            std::shared_ptr<Camera> getCamera() const override { return _camera; }

            /**
             * @brief jump function
             * 
             * @author Adam Lesage
             */
            void jump() override = 0;

            /**
             * @brief apply gravity to the player
             * 
             * @author Adam Lesage
             */
            void applyGravity() override = 0;

            /**
             * @brief handle input, can be input from keyboard or mouse
             * 
             * @author Adam Lesage
             */
            virtual void handleInput() override = 0;

            /**
             * @brief Set the mediator so game can tell when game is over
             * 
             * @author Adam Lesage
             */
            void setMediator(std::shared_ptr<IMediator> mediator) override;

            /**
             * @brief Gameover will be send to RenderEngine that game is over to display end menu screen
             * @author Adam Lesage
             */
            void gameOver() override;

            /**
             * @brief reset camera and all its entities
             * @author Adam Lesage
             */
            void resetGame() override;

        protected:
            std::shared_ptr<Camera> _camera;

            /**
             * @brief The start of the jump
             * 
             * Jump will last 1 second with a curve of 1/2
             * 
             * @author Adam Lesage
             */
            std::chrono::time_point<std::chrono::system_clock> _startOfJump;

            /**
             * @brief Boolean to know if the player is jumping
             * 
             * True if the player is jumping else false
             * 
             * @author Adam Lesage
             */
            bool _isJumping;

            /**
             * @brief Mediator to communicate with different engines
             * 
             * @author Adam Lesage
             */
            std::shared_ptr<IMediator> _mediator;
        private:
    };
}

#endif /* !AGAME_HPP_ */
