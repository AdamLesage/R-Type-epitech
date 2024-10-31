/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ProtocolParsing
*/

#ifndef PROTOCOLPARSING_HPP_
#define PROTOCOLPARSING_HPP_

#include <iostream>
#include <libconfig.h++>
#include <cstring>
#include <map>
#include <utility>
#include <cstring>
#include <iomanip>
#include "../../shared/registry/Registry.hpp"
#include "../../shared/entities/Entity.hpp"
#include "../../shared/systems/Systems.hpp"
#include "../../shared/components/Size.hpp"
#include "../../shared/components/Sprite.hpp"
#include "../../shared/assetEditorParsing/AssetEditorParsing.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace RType {
    class ProtocolParsing {
        public:
            ProtocolParsing(std::string protocolPath, Registry& registry);
            ~ProtocolParsing();

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parsePlayerCreation(const std::string& message, int& index);
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseEntityCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseProjectileCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseMissileCreation(const std::string& message, int& index);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseBigMissileCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseEnemyCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseShieldCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseMachinegunCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseRocketCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseBeamCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseWallCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseRewardCreation(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseEntityDeletion(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parsePositionUpdate(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseHealthUpdate(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseDirectionUpdate(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseObjectCollection(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseProjectileFiring(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseProjectileCollision(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseScoreUpdate(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation
             * and manage the corresponding request (creation, deletion, update)
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseStateChange(const std::string& message, int& index);

            /**
             * @brief Parses and validates a level update message, adjusting the index and handling level-based actions.
             *
             * @param message Reference to the level update message string.
             * @param index Reference to the current parsing position in the message.
             * @return true if parsing is successful and the message is valid; false otherwise.
             */
            bool parseLevelUpdate(const std::string& message, int& index);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             * This function is the main function to parse the message.
             *
             * @param data given by the server. (binary data)
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseData(const std::string& message);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message The time code to parse.
             * @param index The index to update.
             */
            bool parsePingClient(const std::string& message, int& index);

            /**
             * @brief Get the Latency object
             *
             * @return float
             */
            float getLatency() const { return _latency; }

            /**
             * @brief Set the mediator for component communication.
             *
             * Assigns a mediator to facilitate interaction between system components.
             *
             * @param mediator A shared pointer to the mediator instance.
             */
            void setMediator(std::shared_ptr<IMediator> mediator);
            /**
             * @brief Set the game selected by the client.
             * 
             * @param gameSelected The game selected by the client.
             * @return void
             */
            void setGameSelected(const std::string& gameSelected);
        protected:
            /**
             * @brief Check if the message type is valid and if its values are valid.
             *
             * @param messageType The message type to check.
             * @return true if the message type is valid, false otherwise.
             */
            bool checkMessageType(const std::string& messageType, const std::string& message, int& index);

            /**
             * @brief Update the index from the binary data.
             *
             * @param message The message to update.
             * @param index The index to update.
             * @return int The new index.
             */
            int updateIndexFromBinaryData(const std::string& message, int& index);
            /**
             * 
             */
            void loadAssetCfgEditorParsing(size_t level);
        private:
            // Variables
            std::unique_ptr<AssetEditorParsing> _assetEditorParsing;
            libconfig::Config _cfgAssetEditor;
            std::string _protocolPath;
            libconfig::Config _cfg;
            std::map<std::string, std::pair<int, std::string>> _messageTypeMap;
            Registry& _registry; // Will be used to update the game engine data
            float _latency;
            std::shared_ptr<IMediator> _mediator;
             libconfig::Config _gameConfig;

    };
} // namespace RType

#endif /* !PROTOCOLPARSING_HPP_ */
