/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** DoodleJump
*/

#ifndef DOODLEJUMP_HPP_
#define DOODLEJUMP_HPP_

#include <iostream>
#include <memory>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "AGame.hpp"

namespace RType {
    /**
     * @brief DoodleJump class
     * 
     * This class is the DoodleJump game
     * 
     * @class DoodleJump and inherits from AGame
     */
    class DoodleJump : public AGame {
        public:
            /**
             * @brief Construct a new DoodleJump object
             */
            DoodleJump();

            /**
             * @brief Destroy the DoodleJump object
             */
            ~DoodleJump();

            /**
             * @brief handle offline game, meaning there is no communication with the server
             * 
             * Everything is calculated on the client side
             */
            void handleOfflineGame() override;
        protected:
        private:
    };
}

#endif /* !DOODLEJUMP_HPP_ */
