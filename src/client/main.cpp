/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** client
*/

#include <iostream>
#include <memory>
#include "network/Client.hpp"
#include "engines/NetworkEngine.hpp"
#include "engines/RenderingEngine.hpp"
#include "engines/GameEngine.hpp"
#include "engines/PhysicEngine.hpp"
#include "engines/AudioEngine.hpp"
#include "engines/Mediator.hpp"
#include "DLloader.hpp"

int main()
{
    std::unique_ptr<NetworkLib::IClient> client = std::make_unique<NetworkLib::Client>("127.0.0.0", 50000, 50010);

    try {
        std::shared_ptr<RType::NetworkEngine> networkEngine;
        std::shared_ptr<RType::RenderingEngine> renderingEngine;
        std::shared_ptr<RType::GameEngine> gameEngine;
        std::shared_ptr<RType::PhysicEngine> physicEngine;
        std::shared_ptr<RType::AudioEngine> audioEngine;
        DLLoader networkEngineLoader("./lib/libNetworkEngine.so");
        DLLoader renderingEngineLoader("./lib/libRenderingEngine.so");
        DLLoader gameEngineLoader("./lib/libGameEngine.so");
        DLLoader physicEngineLoader("./lib/libPhysicEngine.so");
        DLLoader audioEngineLoader("./lib/libAudioEngine.so");

        networkEngine.reset(networkEngineLoader.getInstance<RType::NetworkEngine>("entryPointNetworkEngine"));
        renderingEngine.reset(renderingEngineLoader.getInstance<RType::RenderingEngine>("entryPointRenderingEngine"));
        gameEngine.reset(gameEngineLoader.getInstance<RType::GameEngine>("entryPointGameEngine"));
        physicEngine.reset(physicEngineLoader.getInstance<RType::PhysicEngine>("entryPointPhysicEngine"));
        audioEngine.reset(audioEngineLoader.getInstance<RType::AudioEngine>("entryPointAudioEngine"));

        RType::Mediator *mediator = new RType::Mediator(gameEngine, networkEngine, renderingEngine);

        gameEngine->run();
    } catch (const RType::DLError &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }

    return (0);
}

    // while (1) {
    //     if (client->hasMessage()) {
    //         std::cout << client->popMessage() << std::endl;
    //     }
    //     networkEngine->doSomething();
    //     sleep(1);
    // }