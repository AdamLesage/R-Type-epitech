/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkEngine
*/

#ifndef NETWORKENGINE_HPP_
#define NETWORKENGINE_HPP_

#include "../AEngine.hpp"
#include "../Mediator/IMediator.hpp"
#include "Client.hpp"

namespace RType {
    class NetworkEngine : public AEngine {
        public:
            NetworkEngine();
            ~NetworkEngine();

            /**
             * @brief Run current instance of the engine.
             */
            void run() override;
            
            /**
             * @brief Send a message to the game engine, it will call the mediator to send the message to the game engine.
            */
            void updateData();

        protected:
            std::unique_ptr<NetworkLib::IClient> _client;
        private:
    };
}

#endif /* !NETWORKENGINE_HPP_ */
