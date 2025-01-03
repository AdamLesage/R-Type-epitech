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
#include "targetver.h"

namespace RType {
    class NetworkEngine : public AEngine {
        public:
            NetworkEngine();
            NetworkEngine(std::string host, unsigned short server_port, unsigned short local_port = 50010);
            ~NetworkEngine();

            /**
             * @brief Run current instance of the engine.
             */
            void run() override;

            /**
             * @brief Send a message to the game engine, it will call the mediator to send the message to the
             * game engine.
             */
            void updateData();

            /**
             * @brief Set the mediator of the engine and of the client.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator) override;

            void setParams(std::string host, unsigned short server_port, unsigned short local_port);

            void setEnd();
            std::unique_ptr<NetworkLib::IClient>
                _client; // Public attribute to be able to access it from Mediator.
        protected:
        private:
            bool _running = true;
    };
} // namespace RType

#endif /* !NETWORKENGINE_HPP_ */
