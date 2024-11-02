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
#include "../../shared/assetEditorParsing/AssetEditorParsing.hpp"
#include "./NetworkSender.hpp"
#include "../../shared/utils/Logger.hpp"
#include <memory>
#include "../../shared/components/ScoreValue.hpp"

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

        /**
         * @brief Return true if all players are dead else false
         * @return True if all players are dead else false
         * @author Adam Lesage
         */
        bool areAllPlayersDead();

        /**
         * @brief Check if friendly fire is enabled by reading the configuration file key.cfg.
         *
         * @return true if friendly fire is enabled, false otherwise.
         */
        bool getfriendlyfire();

    protected:
    private:
        Registry reg;
        Systems sys;
        std::shared_ptr<NetworkLib::Server> network;
        std::unique_ptr<NetworkSender> _networkSender;
        std::thread receiverThread;
        std::thread connectionManagmentThread;
        int frequency;
        RType::Logger logger;
        bool running;
        bool friendlyfire;
        std::mutex _mutex;
        /**
         * @brief Delete all entity at the end of the game
         */
        void clearGame();
        /**
         * @brief listen to the server socket to manage client input
         */
        void handleRecieve();
        /**
         * @brief lunch a game with connected player
         */
        void startGame(int idEntity);
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
         * @brief spawn a wave of ennemy
         *
         */
        void spawnWave();
        /**
         * @brief andle the input of the client
         *
         * @param messsage message of the input
         */
        void handleClientInput(std::pair<std::string, uint32_t> message);

        /**
         * @brief Handle a new client connection and perform any setup required for the client.
         */
        void handleClientConnection();

        /**
         * @brief handle the change of level
         *
         */
        void handleChangeLevel(unsigned int);

        /**
         * @brief handle the Inpute of the client
         *
         * @param message the message send by the client
         * @return std::vector<char> the array with the input key in the order: [up, down, left, right, shoot]
         */
        std::array<char, 6> retrieveInputKeys();

        /**
         * @brief update the Level config at level change
         */
        void updateLevelConfig();

        /**
         * @brief add a Enemy on the registry and send a notification to connected client
         *
         * @param type the type off entity
         * @param position_x the x position of the entity
         * @param position_y the y position of the entity
         *
         */
        void spawnCustomEntity(char type, float position_x, float position_y, size_t entity);

        std::map<size_t, size_t> playersId;
        libconfig::Config _gameConfig;
        libconfig::Config _levelConfig;
        std::unique_ptr<AssetEditorParsing> assetEditorParsing;
        bool ennemyAlive           = true;
        float _camera_x            = 1920;
        unsigned int _currentLevel = 0;
};

#endif /* !GAMELOGIQUE_HPP_ */
