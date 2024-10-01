/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** client
*/

#include <iostream>
#include <memory>
#include <stdexcept>

#include "NetworkEngine/NetworkEngine.hpp"
#include "RenderEngine/RenderingEngine.hpp"
#include "GameEngine/GameEngine.hpp"
#include "PhysicEngine/PhysicEngine.hpp"
#include "AudioEngine/AudioEngine.hpp"
#include "Mediator/Mediator.hpp"
#include "DLloader.hpp"

template <typename EngineType>
std::shared_ptr<EngineType> loadEngine(DLLoader &loader, const std::string &entryPoint) {
    return std::shared_ptr<EngineType>(loader.getInstance<EngineType>(entryPoint));
}

void runEngines(std::shared_ptr<RType::GameEngine> gameEngine, std::shared_ptr<RType::NetworkEngine> networkEngine, std::shared_ptr<RType::RenderingEngine> renderingEngine, std::shared_ptr<RType::PhysicEngine> physicEngine, std::shared_ptr<RType::AudioEngine> audioEngine)
{
    // Run each engine in a separate thread
    std::thread gameThread([&gameEngine]() {
        gameEngine->run();
    });

    std::thread networkThread([&networkEngine]() {
        networkEngine->run();
    });

    std::thread renderingThread([&renderingEngine]() {
        renderingEngine->run();
    });

    std::thread physicThread([&physicEngine]() {
        physicEngine->run();
    });

    std::thread audioThread([&audioEngine]() {
        audioEngine->run();
    });

    // Wait for all threads to finish
    gameThread.join();
    networkThread.join();
    renderingThread.join();
    physicThread.join();
    audioThread.join();
}

int main()
{
    try {
        // Initialize loaders for each engine
        DLLoader networkEngineLoader("./lib/libNetworkEngine.so");
        DLLoader renderingEngineLoader("./lib/libRenderingEngine.so");
        DLLoader gameEngineLoader("./lib/libGameEngine.so");
        DLLoader physicEngineLoader("./lib/libPhysicEngine.so");
        DLLoader audioEngineLoader("./lib/libAudioEngine.so");

        // Load all engines dynamically
        auto networkEngine = loadEngine<RType::NetworkEngine>(networkEngineLoader, "entryPointNetworkEngine");
        auto renderingEngine = loadEngine<RType::RenderingEngine>(renderingEngineLoader, "entryPointRenderingEngine");
        auto gameEngine = loadEngine<RType::GameEngine>(gameEngineLoader, "entryPointGameEngine");
        auto physicEngine = loadEngine<RType::PhysicEngine>(physicEngineLoader, "entryPointPhysicEngine");
        auto audioEngine = loadEngine<RType::AudioEngine>(audioEngineLoader, "entryPointAudioEngine");

        // Use unique_ptr for mediator to ensure memory management
        // Cannot use shared or unique pointer because it segfaults
        RType::Mediator *mediator = new RType::Mediator(gameEngine, networkEngine, renderingEngine, physicEngine, audioEngine);

        runEngines(gameEngine, networkEngine, renderingEngine, physicEngine, audioEngine);
    } catch (const RType::DLError &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}
