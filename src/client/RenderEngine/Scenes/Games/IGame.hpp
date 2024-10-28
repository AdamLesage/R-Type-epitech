/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "../../../Camera.hpp"

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
             */
            virtual ~IGame() = default;

            /**
             * @brief handle offline game, meaning there is no communication with the server
             */
            virtual void handleOfflineGame() = 0;

            /**
             * @brief Returns the current instance of the camera
             * 
             * @return std::shared_ptr<Camera> the camera
             */
            virtual std::shared_ptr<Camera> getCamera() const = 0;
        protected:
        private:
    };
}

#endif /* !IGAME_HPP_ */
