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
#include "../NetworkEngine/NetworkEngine.hpp"
#include "../RenderEngine/RenderingEngine.hpp"
#include "../PhysicEngine/PhysicEngine.hpp"
#include "../AudioEngine/AudioEngine.hpp"
#include "../../shared/entities/Entity.hpp"
#include "../../shared/registry/Registry.hpp"
#include "../../shared/systems/Systems.hpp"
#include "ProtocolParsing.hpp"
#include "../Camera.hpp"
#include <mutex>

#ifdef _WIN32
    #include <Windows.h>
    #define PATH_SEPARATOR "\\"
#else
    #include <unistd.h>
    #define PATH_SEPARATOR "/"
#endif

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
             * @brief Send a message to the network, it will call the mediator to send the message to the
             * network engine.
             *
             * @param message The message to send.
             */
            void send(const std::string& message);

            /**
             * @brief Handle the server data, received from the Mediator notified by the NetworkEngine.
             *  It will update the registry and the systems. Such as create entities, update entities, delete
             * entities, etc.
             *
             * @param message The message received from the server. Need to be parsed.
             */
            void handleServerData(const std::string& message);

            /**
             * @brief Set the engines for the game engine.
             *
             * @param networkEngine The network engine.
             * @param renderingEngine The rendering engine.
             * @param physicEngine The physic engine.
             * @param audioEngine The audio engine.
             */
            void setEngines(std::shared_ptr<NetworkEngine> networkEngine,
                            std::shared_ptr<RenderingEngine> renderingEngine,
                            std::shared_ptr<PhysicEngine> physicEngine,
                            std::shared_ptr<AudioEngine> audioEngine);

            /**
             * @brief Set the mediator of the engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator) override;
            /**
             * @brief Update the Camera with the _registery info and send change to RenderEngine
             */
            void updateCamera();

            /**
             * @brief Set the game selected by the client.
             * 
             * @param gameSelected The game selected by the client.
             * @return void
             */
            void setGameSelected(const std::string& gameSelected) { _gameSelected = gameSelected; }

        protected:
        private:
            Registry _registry;
            libconfig::Config _playerConfig;
            std::unique_ptr<RType::ProtocolParsing> _protocolParsing;
            std::shared_ptr<NetworkEngine> _networkEngine;
            std::shared_ptr<RenderingEngine> _renderingEngine;
            std::shared_ptr<PhysicEngine> _physicEngine;
            std::shared_ptr<AudioEngine> _audioEngine;
            std::shared_ptr<Camera> _camera;
            std::shared_ptr<std::mutex> _mutex;
            std::string _gameSelected;
    };
} // namespace RType

#endif /* !GAMEENGINE_HPP_ */
