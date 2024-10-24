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
#include "../PhysicEngine/PhysicEngine.hpp"
#include "../AudioEngine/AudioEngine.hpp"

namespace RType {
    class Mediator : public IMediator {
        public:
            Mediator(std::shared_ptr<GameEngine> gameEngine,
                     std::shared_ptr<NetworkEngine> networkEngine,
                     std::shared_ptr<RenderingEngine> renderingEngine,
                     std::shared_ptr<PhysicEngine> physicEngine,
                     std::shared_ptr<AudioEngine> audioEngine);
            ~Mediator();

            void notify(std::string sender, const std::string& event) override;
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
            void notifyGameEngine(std::string sender, const std::string& event);

            /**
             * @brief Notify the network engine of an event.
             *
             * @param sender The sender of the event.
             * @param event The event to notify.
             */
            void notifyNetworkEngine(std::string sender, const std::string& event);

            /**
             * @brief Notify the rendering engine of an event.
             *
             * @param sender The sender of the event.
             * @param event The event to notify.
             */
            void notifyRenderingEngine(std::string sender, const std::string& event);

            /**
             * @brief Notify the physic engine of an event.
             *
             * @param sender The sender of the event.
             * @param event The event to notify.
             */
            void notifyPhysicEngine(std::string sender, const std::string& event);

            /**
             * @brief Notify the audio engine of an event.
             *
             * @param sender The sender of the event.
             * @param event The event to notify.
             */
            void notifyAudioEngine(std::string sender, const std::string& event);

            /**
             * @brief Notify the protocol parsing system of an event.
             *
             * This function is responsible for manage notify from ProtocolParsing
             *
             * @param sender The sender of the event.
            * @param event The event to notify.
            */
            void notifyProtocolParsing(std::string sender, const std::string& event);

        private:
            std::shared_ptr<GameEngine> _gameEngine;
            std::shared_ptr<NetworkEngine> _networkEngine;
            std::shared_ptr<RenderingEngine> _renderingEngine;
            std::shared_ptr<PhysicEngine> _physicEngine;
            std::shared_ptr<AudioEngine> _audioEngine;
    };
} // namespace RType

#endif /* !MEDIATOR_HPP_ */
