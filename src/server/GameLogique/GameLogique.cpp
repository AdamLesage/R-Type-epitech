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

void GameLogique::spawnEnnemy(char type, float position_x, float position_y)
{
    size_t entity = this->reg.spawn_entity();
    char data[13];

    switch (type)
    {
    case 0x03:
        this->reg.add_component<Position>(entity, Position{position_x, position_y});
        this->reg.add_component<Velocity>(entity, Velocity{-1, 0});
        this->reg.add_component<Health>(entity, Health{100});
        this->reg.add_component<Damage>(entity, Damage{20});
        this->reg.add_component<Wave_pattern>(entity, Wave_pattern{1.f, 0.02f});
        break;
    default:
        this->reg.add_component<Position>(entity, Position{position_x, position_y});
        this->reg.add_component<Velocity>(entity, Velocity{-1, 0});
        this->reg.add_component<Health>(entity, Health{100});
        this->reg.add_component<Damage>(entity, Damage{20});
        this->reg.add_component<Wave_pattern>(entity, Wave_pattern{1.f, 0.02f});
        break;
    }
    data[0] = type;
    std::memcpy(&data[1], &entity, sizeof(entity));
    std::memcpy(&data[5], &position_x, sizeof(float));
    std::memcpy(&data[9], &position_y, sizeof(float));
    this->network->sendToAll(data);
}

void GameLogique::runGame() {
    std::clock_t clock = std::clock();
    std::clock_t spawnClock = std::clock();
    while(1) {
        if (static_cast<float>(std::clock() - clock) / CLOCKS_PER_SEC > 1 / frequency) {
            clock = std::clock();
            sys.wave_pattern_system(reg, static_cast<float>(clock) / CLOCKS_PER_SEC);
            sys.position_system(reg);     
        }
        if (static_cast<float>(std::clock() - spawnClock) / CLOCKS_PER_SEC > 2) {
            this->spawnEnnemy(0x03, 1000, 500);
            spawnClock = std::clock();
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