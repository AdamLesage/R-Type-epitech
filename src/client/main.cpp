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

// Mutex to protect the access to the mediator, they need to be global to be accessible by all threads
std::mutex gameMutex;
std::mutex networkMutex;
std::mutex renderingMutex;
std::mutex physicMutex;
std::mutex audioMutex;

void errorHandling(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: " << av[0] << " <host> <port>" << std::endl;
        exit(84);
    }
    if (std::stoi(av[2]) < 1024 || std::stoi(av[2]) > 65535) {
        std::cerr << "Port must be between 1024 and 65535" << std::endl;
        exit(84);
    }
    if (std::string(av[1]).size() < 7) {
        std::cerr << "Host must be at least 7 characters long" << std::endl;
        exit(84);
    }
}

template <typename EngineType>
std::shared_ptr<EngineType> loadEngine(std::shared_ptr<DLLoader> loader, const std::string &entryPoint) {
    return std::shared_ptr<EngineType>(loader->getInstance<EngineType>(entryPoint));
}

void runEngines(std::shared_ptr<RType::GameEngine> gameEngine, std::shared_ptr<RType::NetworkEngine> networkEngine, std::shared_ptr<RType::RenderingEngine> renderingEngine, std::shared_ptr<RType::PhysicEngine> physicEngine, std::shared_ptr<RType::AudioEngine> audioEngine)
{
    // Run each engine in a separate thread
    std::thread gameThread([&gameEngine]() {
        std::lock_guard<std::mutex> lock(gameMutex); // Lock the mutex
        gameEngine->run();
    });

    std::thread networkThread([&networkEngine]() {
        std::lock_guard<std::mutex> lock(networkMutex); // Lock the mutex
        networkEngine->run();
    });

    std::thread renderingThread([&renderingEngine]() {
        std::lock_guard<std::mutex> lock(renderingMutex); // Lock the mutex
        renderingEngine->run();
    });

    std::thread physicThread([&physicEngine]() {
        std::lock_guard<std::mutex> lock(physicMutex); // Lock the mutex
        physicEngine->run();
    });

    std::thread audioThread([&audioEngine]() {
        std::lock_guard<std::mutex> lock(audioMutex); // Lock the mutex
        audioEngine->run();
    });

    // Wait for all threads to finish
    gameThread.join();
    networkThread.join();
    renderingThread.join();
    physicThread.join();
    audioThread.join();
}

int main(int ac, char **av)
{
    errorHandling(ac, av);

    std::string host = av[1];
    unsigned short server_port = static_cast<unsigned short>(std::stoi(av[2]));
    unsigned short local_port = 0;
    std::shared_ptr<DLLoader> networkEngineLoader;
    std::shared_ptr<DLLoader> renderingEngineLoader;
    std::shared_ptr<DLLoader> gameEngineLoader;
    std::shared_ptr<DLLoader> physicEngineLoader;
    std::shared_ptr<DLLoader> audioEngineLoader;

    try {
        try {
            networkEngineLoader.reset(new DLLoader("./lib/libNetworkEngine.so"));
        } catch (const RType::DLError &e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            renderingEngineLoader.reset(new DLLoader("./lib/libRenderingEngine.so"));
        } catch (const RType::DLError &e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            gameEngineLoader.reset(new DLLoader("./lib/libGameEngine.so"));
        } catch (const RType::DLError &e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            physicEngineLoader.reset(new DLLoader("./lib/libPhysicEngine.so"));
        } catch (const RType::DLError &e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            audioEngineLoader.reset(new DLLoader("./lib/libAudioEngine.so"));
        } catch (const RType::DLError &e) {
            std::cerr << e.what() << std::endl;
        }

        // Initialize loaders for each engine
        auto networkEngine = loadEngine<RType::NetworkEngine>(networkEngineLoader, "entryPointNetworkEngine");
        networkEngine->setParams(host, server_port, local_port);
        auto renderingEngine = loadEngine<RType::RenderingEngine>(renderingEngineLoader, "entryPointRenderingEngine");
        auto gameEngine = loadEngine<RType::GameEngine>(gameEngineLoader, "entryPointGameEngine");
        auto physicEngine = loadEngine<RType::PhysicEngine>(physicEngineLoader, "entryPointPhysicEngine");
        auto audioEngine = loadEngine<RType::AudioEngine>(audioEngineLoader, "entryPointAudioEngine");


        // // Handle the case where not all engines are loaded
        RType::Mediator *mediator = new RType::Mediator(gameEngine, networkEngine, renderingEngine, physicEngine, audioEngine);

        gameEngine->setEngines(networkEngine, renderingEngine, physicEngine, audioEngine);
        gameEngine->run();
    } catch (const RType::DLError &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}
