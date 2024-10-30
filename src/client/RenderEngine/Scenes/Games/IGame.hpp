/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "../../../Camera.hpp"
#include "../../../Mediator/IMediator.hpp"

#include <memory>

namespace RType {
    /**
     * @brief IGame class
     * 
     * This class is the interface for all games
     */
    class IGame {
        public:
            /**
             * @brief Construct a new IGame object
             * @author Adam Lesage
             */
            virtual ~IGame() = default;

            /**
             * @brief handle offline game, meaning there is no communication with the server
             * @author Adam Lesage
             */
            virtual void handleOfflineGame() = 0;

            /**
             * @brief Returns the current instance of the camera
             * @return std::shared_ptr<Camera> the camera
             * @author Adam Lesage
             */
            virtual std::shared_ptr<Camera> getCamera() const = 0;

            /**
             * @brief jump function
             * @author Adam Lesage
             */
            virtual void jump() = 0;

            /**
             * @brief apply gravity to the player
             * @author Adam Lesage
             */
            virtual void applyGravity() = 0;

            /**
             * @brief handle input, can be input from keyboard or mouse
             * @author Adam Lesage
             */
            virtual void handleInput() = 0;

            /**
             * @brief Set the mediator so game can tell when game is over
             * @param mediator Mediator to set
             * @author Adam Lesage
             */
            virtual void setMediator(std::shared_ptr<IMediator> mediator) = 0;

            /**
             * @brief Gameover will be send to RenderEngine that game is over to display end menu screen
             * @author Adam Lesage
             */
            virtual void gameOver() = 0;

            /**
             * @brief reset camera and all its entities
             * @author Adam Lesage
             */
            virtual void resetGame() = 0;
        protected:
        private:
    };
}

#endif /* !IGAME_HPP_ */
