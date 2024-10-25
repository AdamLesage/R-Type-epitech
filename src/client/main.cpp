/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** client
*/

#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <mutex>

#include "RenderEngine/Menu/ClientConnexionHandling.hpp"
#include "NetworkEngine/NetworkEngine.hpp"
#include "RenderEngine/RenderingEngine.hpp"
#include "GameEngine/GameEngine.hpp"
#include "PhysicEngine/PhysicEngine.hpp"
#include "AudioEngine/AudioEngine.hpp"
#include "Mediator/Mediator.hpp"
#include "DLloader.hpp"
#include "../shared/utils/Logger.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define LIB_EXTENSION ".dll"
#define PATH_SEPARATOR "\\"
#else
#include <dlfcn.h>
#define LIB_EXTENSION ".so"
#define PATH_SEPARATOR "/"
#endif

std::mutex gameMutex;
std::mutex networkMutex;
std::mutex renderingMutex;
std::mutex physicMutex;
std::mutex audioMutex;

void errorHandling(int ac, char** av) {
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
std::shared_ptr<EngineType> loadEngine(std::shared_ptr<DLLoader> loader, const std::string& entryPoint) {
    return std::shared_ptr<EngineType>(loader->getInstance<EngineType>(entryPoint));
}

void runEngines(std::shared_ptr<RType::GameEngine> gameEngine,
                std::shared_ptr<RType::NetworkEngine> networkEngine,
                std::shared_ptr<RType::RenderingEngine> renderingEngine,
                std::shared_ptr<RType::PhysicEngine> physicEngine,
                std::shared_ptr<RType::AudioEngine> audioEngine) {
    std::thread gameThread([&gameEngine]() {
        std::lock_guard<std::mutex> lock(gameMutex);
        gameEngine->run();
    });

    std::thread networkThread([&networkEngine]() {
        std::lock_guard<std::mutex> lock(networkMutex);
        networkEngine->run();
    });

    std::thread renderingThread([&renderingEngine]() {
        std::lock_guard<std::mutex> lock(renderingMutex);
        renderingEngine->run();
    });

    std::thread physicThread([&physicEngine]() {
        std::lock_guard<std::mutex> lock(physicMutex);
        physicEngine->run();
    });

    std::thread audioThread([&audioEngine]() {
        std::lock_guard<std::mutex> lock(audioMutex);
        audioEngine->run();
    });

    gameThread.join();
    networkThread.join();
    renderingThread.join();
    physicThread.join();
    audioThread.join();
}

std::string getLibraryPath(const std::string& libName) {
    return std::string(".") + PATH_SEPARATOR + "lib" + PATH_SEPARATOR + libName + LIB_EXTENSION;
}

bool isNumber(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

int main(int ac, char** av) {
    // errorHandling(ac, av);
    (void)ac;

    std::string host           = "";
    unsigned short server_port = 0;
    std::string gameSelected   = "";

    if (av[1] != nullptr && av[2] != nullptr && isNumber(av[2])) {
        host        = av[1];
        server_port = static_cast<unsigned short>(std::stoi(av[2]));
    }
    unsigned short local_port = 0;
    std::shared_ptr<DLLoader> networkEngineLoader;
    std::shared_ptr<DLLoader> renderingEngineLoader;
    std::shared_ptr<DLLoader> gameEngineLoader;
    std::shared_ptr<DLLoader> physicEngineLoader;
    std::shared_ptr<DLLoader> audioEngineLoader;

    RType::Logger logger;
    if (std::string(PATH_SEPARATOR) == "\\") {
        logger.log(RType::Logger::LogType::RTYPEINFO, "Running R-Type on Windows.");
    } else {
        logger.log(RType::Logger::LogType::RTYPEINFO, "Running R-Type on Unix.");
    }

    try {
        try {
            networkEngineLoader.reset(new DLLoader(getLibraryPath("libNetworkEngine")));
        } catch (const RType::DLError& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            renderingEngineLoader.reset(new DLLoader(getLibraryPath("libRenderingEngine")));
        } catch (const RType::DLError& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            gameEngineLoader.reset(new DLLoader(getLibraryPath("libGameEngine")));
        } catch (const RType::DLError& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            physicEngineLoader.reset(new DLLoader(getLibraryPath("libPhysicEngine")));
        } catch (const RType::DLError& e) {
            std::cerr << e.what() << std::endl;
        }

        try {
            audioEngineLoader.reset(new DLLoader(getLibraryPath("libAudioEngine")));
        } catch (const RType::DLError& e) {
            std::cerr << e.what() << std::endl;
        }

        // Ask for host and port to client
        std::shared_ptr<RType::ClientConnexionHandling> clientConnexionHandling =
            std::make_shared<RType::ClientConnexionHandling>(host, server_port);
        clientConnexionHandling->displayConnexionWindow();
        host        = clientConnexionHandling->getHost();
        server_port = clientConnexionHandling->getServerPort();
        gameSelected = clientConnexionHandling->getGameSelected();

        auto networkEngine = loadEngine<RType::NetworkEngine>(networkEngineLoader, "entryPointNetworkEngine");
        networkEngine->setParams(host, server_port, local_port);
        auto gameEngine   = loadEngine<RType::GameEngine>(gameEngineLoader, "entryPointGameEngine");
        auto physicEngine = loadEngine<RType::PhysicEngine>(physicEngineLoader, "entryPointPhysicEngine");
        auto audioEngine  = loadEngine<RType::AudioEngine>(audioEngineLoader, "entryPointAudioEngine");
        auto renderingEngine =
            loadEngine<RType::RenderingEngine>(renderingEngineLoader, "entryPointRenderingEngine");

        RType::Mediator* mediator =
            new RType::Mediator(gameEngine, networkEngine, renderingEngine, physicEngine, audioEngine);
        (void)mediator;
        gameEngine->setEngines(networkEngine, renderingEngine, physicEngine, audioEngine);
        gameEngine->run();
    } catch (const RType::DLError& e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}
