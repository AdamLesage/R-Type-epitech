/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "../AEngine.hpp"
#include "../Mediator/IMediator.hpp"
#include "../../shared/entities/Entity.hpp"
#include "../../shared/registry/Registry.hpp"
#include "../../shared/systems/Systems.hpp"

namespace RType {
    class GameEngine : public AEngine {
        public:
            GameEngine();
            ~GameEngine();

            /**
             * @brief Run current instance of the engine.
             */
            void run() override;

            /**
             * @brief Send a message to the network, it will call the mediator to send the message to the network engine.
             *
             * @param message The message to send.
            */
            void send(const std::string &message);
        protected:
        private:
            Registry _registry;
            Systems _systems;
            sf::RenderWindow _window;
    };
}

#endif /* !GAMEENGINE_HPP_ */