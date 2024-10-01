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
#include <string.h>
#include <map>
#include <utility>


namespace RType {
    class ProtocolParsing {
        public:
            ProtocolParsing(std::string protocolPath);
            ~ProtocolParsing();
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parsePlayerCreation(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseProjectileCreation(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseEnemyCreation(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseBonusCreation(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseWallCreation(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseRewardCreation(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseEntityDeletion(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parsePositionUpdate(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseHealthUpdate(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseDirectionUpdate(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseObjectCollection(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseProjectileFiring(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseProjectileCollision(const char *message);
            
            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseScoreUpdate(const char *message);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             *
             * @param message A pointer to a C-string containing the message to be parsed.
             * @return true if the parsing is successful and the message is valid, false otherwise.
             */
            bool parseStateChange(const char *message);

            /**
             * @brief Parse the message to validate and extract information for the corresponding operation.
             * This function is the main function to parse the message.
             * 
             * @param data given by the server. (binary data)
             * @return true if the parsing is successful and the message is valid, false otherwise.
            */
            bool parseData(const char *message);

        protected:
            /**
             * @brief Check if the message type is valid and if its values are valid.
             * 
             * @param messageType The message type to check.
             * @return true if the message type is valid, false otherwise.
            */
            bool checkMessageType(const std::string &messageType, const char *message);
        private:
            // Variables
            std::string _protocolPath;
            libconfig::Config _cfg;
            std::map<std::string, std::pair<int, std::string>> _messageTypeMap;
    };
}

#endif /* !PROTOCOLPARSING_HPP_ */
