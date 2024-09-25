/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameLogique
*/

#include "GameLogique.hpp"

GameLogique::GameLogique(size_t port, int _frequency)
{
    this->network = std::make_shared<NetworkLib::Server>(port);
    this->receiverThread = std::thread(&GameLogique::handleRecieve, this);
    this->running = false;
    this->frequency = _frequency;
}

GameLogique::~GameLogique()
{
    receiverThread.join();
}

void GameLogique::startGame() {
    if (running == false) {
        std::cout << network->getClientCount() << std::endl;
        for (size_t i = 0; i != network->getClientCount(); i++) {
            size_t entity = this->reg.spawn_entity();
            this->reg.add_component<Position>(entity, Position_s{100.f + (100.f * i), 100.f});
            this->reg.add_component<Velocity>(entity, Velocity_s{0.f, 0.f});
            this->reg.add_component<Tag>(entity, Tag{"player"});
            char data[13];
            data[0] = 0x01;
            std::memcpy(&data[1], &entity, sizeof(entity));
            std::memcpy(&data[5], &this->reg.get_components<Position>()[entity]->x, sizeof(float));
            std::memcpy(&data[9], &this->reg.get_components<Position>()[entity]->y, sizeof(float));
            this->network->sendToAll(data);
        }
        this->running = true;
    }
}

void GameLogique::runGame() {
    std::clock_t clock = std::clock();
    while(1) {
        if (static_cast<float>(std::clock() - clock) / CLOCKS_PER_SEC > 1 / frequency) {
            network->sendToAll("test");
        }
    }
}

void GameLogique::handleRecieve()
{
    while (1)
    {
        if (network->hasMessages()) {
            std::pair<std::string, uint32_t> message = network->popMessage();
            std::cout << "message: " << (int)message.first[0] << " Size: "<< message.second << std::endl;
            switch (message.first[0])
            {
            case 0x41:
                startGame();
                break;
            default:
                std::cout << "unknowCommand" << std::endl;
                break;
            }
        }
    }
}