/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameLogique
*/

#ifndef GAMELOGIQUE_HPP_
#define GAMELOGIQUE_HPP_

#include "../../shared/registry/Registry.hpp"
#include "../systems/Systems.hpp"
#include "../network/Server.hpp"
#include "../../shared/components/Tag.hpp"
#include "../../shared/components/Position.hpp"
#include "../../shared/components/Velocity.hpp"
#include "../../shared/components/Shoot.hpp"
#include "../../shared/components/ShootingSpeed.hpp"
#include "./NetworkSender.hpp"
#include "../../shared/utils/Logger.hpp"
#include <memory>

#if defined(_WIN32) || defined(_WIN64)
    #define PATH_SEPARATOR "\\"
#else
    #define PATH_SEPARATOR "/"
#endif

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
        std::unique_ptr<NetworkSender> _networkSender;
        std::thread receiverThread;
        int frequency;
        RType::Logger logger;
        bool running;
        std::mutex _mutex;
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
        void spawnEnnemy(char type, float position_x, float position_y);
        /**
         * @brief handle the Inpute of the client
         *
         * @param message the message send by the client
         *
        */
        void handleClientInput(std::pair<std::string, uint32_t> message);

        /**
         * @brief handle the Inpute of the client
         *
         * @param message the message send by the client
         * @return std::vector<char> the array with the input key in the order: [up, down, left, right, shoot]
        */
        std::array<char, 6> retrieveInputKeys();
};

#endif /* !GAMELOGIQUE_HPP_ */
