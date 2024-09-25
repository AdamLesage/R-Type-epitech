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
#include "engines/Mediator.hpp"

int main()
{
    std::unique_ptr<NetworkLib::IClient> client = std::make_unique<NetworkLib::Client>("127.0.0.0", 50000, 50010);

    std::shared_ptr<NetworkEngine> networkEngine = std::make_shared<NetworkEngine>();
    std::shared_ptr<RenderingEngine> renderingEngine = std::make_shared<RenderingEngine>();
    std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
    Mediator *mediator = new Mediator(gameEngine, networkEngine, renderingEngine);

    gameEngine->run();

    return (0);
}

    // while (1) {
    //     if (client->hasMessage()) {
    //         std::cout << client->popMessage() << std::endl;
    //     }
    //     networkEngine->doSomething();
    //     sleep(1);
    // }