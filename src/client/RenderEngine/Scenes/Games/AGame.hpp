/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AGame
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "IGame.hpp"

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
            std::shared_ptr<Camera> getCamera() const { return _camera; }

        protected:
            std::shared_ptr<Camera> _camera;
        private:
    };
}

#endif /* !AGAME_HPP_ */
