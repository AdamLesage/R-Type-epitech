/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RType
*/

#ifndef RTYPEOFFLINE_HPP_
#define RTYPEOFFLINE_HPP_

#include <iostream>
#include <memory>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "AGame.hpp"

namespace RType {
    /**
     * @brief RTypeOffline class is the logic loaded from client for offline mode gameplay
     */
    class RTypeOffline : public AGame {
        public:
            RTypeOffline();
            ~RTypeOffline();

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
    };
}

#endif /* !RTYPEOFFLINE_HPP_ */
