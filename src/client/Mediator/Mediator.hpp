/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Mediator
*/

#ifndef MEDIATOR_HPP_
#define MEDIATOR_HPP_

#include <string>
#include <memory>
#include "IMediator.hpp"
#include "../GameEngine/GameEngine.hpp"
#include "../NetworkEngine/NetworkEngine.hpp"
#include "../RenderEngine/RenderingEngine.hpp"

namespace RType {
    class Mediator : public IMediator {
        public:
            Mediator(std::shared_ptr<GameEngine> gameEngine, std::shared_ptr<NetworkEngine> networkEngine, std::shared_ptr<RenderingEngine> renderingEngine);
            ~Mediator();

            void notify(std::string sender, std::string event) override;
            /**
             * @brief Notify the engine of an event.
             *
             * @param sender The sender of the event.
             * @param event The event to notify.
             */
        protected:
            /**
             * @brief Notify the game engine of an event.
             * 
             * @param sender The sender of the event.
             * @param event The event to notify.
            */
            void notifyGameEngine(std::string sender, std::string event);

            /**
             * @brief Notify the network engine of an event.
             * 
             * @param sender The sender of the event.
             * @param event The event to notify.
            */
            void notifyNetworkEngine(std::string sender, std::string event);

            /**
             * @brief Notify the rendering engine of an event.
             * 
             * @param sender The sender of the event.
             * @param event The event to notify.
            */
            void notifyRenderingEngine(std::string sender, std::string event);
        private:
            std::shared_ptr<GameEngine> _gameEngine;
            std::shared_ptr<NetworkEngine> _networkEngine;
            std::shared_ptr<RenderingEngine> _renderingEngine;
    };
}

#endif /* !MEDIATOR_HPP_ */
