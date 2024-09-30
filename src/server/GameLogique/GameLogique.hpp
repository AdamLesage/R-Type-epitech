/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameLogique
*/

#ifndef GAMELOGIQUE_HPP_
#define GAMELOGIQUE_HPP_

#include "../registry/Registry.hpp"
#include "../systems/Systems.hpp"
#include "../network/Server.hpp"
#include "../../shared/components/Tag.hpp"
#include "../../shared/components/Position.hpp"
#include "../../shared/components/Velocity.hpp"
#include <memory>

class GameLogique {
    public:
        /**
         * @brief manage the game logique with client input
         *
         * @param port the port which the server is connected
         * @param frequency the frequency of the game
         */
        GameLogique(size_t port, int frequency = 200);
        ~GameLogique();
        /**
         * @brief update entity every 1 / frequency second
         */
        void runGame();
    protected:
    private:
        Registry reg;
        Systems sys;
        std::shared_ptr<NetworkLib::Server> network;
        std::thread receiverThread;
        int frequency;
        bool running;
        /**
         * @brief listen to the server socket to manage client input
        */
        void handleRecieve();
        /**
         * @brief lunch a game with connected player
        */
        void startGame();
        /**
         * @brief add a Enemy on the registry and send a notification to connected client
         * 
         * @param type the type off ennemy
         * @param position_x the x position of the ennemy
         * @param position_y the y position of the ennemy
         * 
        */
        void GameLogique::spawnEnnemy(char type, float position_x, float position_y)
};
#endif /* !GAMELOGIQUE_HPP_ */
