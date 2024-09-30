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
    this->_networkSender = std::make_unique<NetworkSender>(this->network);
    this->receiverThread = std::thread(&GameLogique::handleRecieve, this);
    this->running = false;
    this->frequency = _frequency;
    this->reg.register_component<Position>();
    this->reg.register_component<Velocity>();
    this->reg.register_component<Tag>();
    this->reg.register_component<Health>();
    this->reg.register_component<Damage>();
    this->reg.register_component<Wave_pattern>();
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
            float xPos = 100.f + (100.f * i);
            float yPos = 100.f;
            this->reg.add_component<Position>(entity, Position_s{100.f + (100.f * i), 100.f});
            this->reg.add_component<Velocity>(entity, Velocity_s{0.f, 0.f});
            this->reg.add_component<Tag>(entity, Tag{"player"});
            this->_networkSender->sendCreatePlayer(entity, xPos, yPos);
        }
        this->running = true;
    }
}

void GameLogique::spawnEnnemy(char type, float position_x, float position_y)
{
    size_t entity = this->reg.spawn_entity();

    switch (type)
    {
    case 0x03:
        this->reg.add_component<Position>(entity, Position{position_x, position_y});
        this->reg.add_component<Velocity>(entity, Velocity{-1, 0});
        this->reg.add_component<Health>(entity, Health{100, true});
        this->reg.add_component<Damage>(entity, Damage{20});
        this->reg.add_component<Wave_pattern>(entity, Wave_pattern{1.f, 0.02f});
        break;
    default:
        this->reg.add_component<Position>(entity, Position{position_x, position_y});
        this->reg.add_component<Velocity>(entity, Velocity{-1, 0});
        this->reg.add_component<Health>(entity, Health{100, true});
        this->reg.add_component<Damage>(entity, Damage{20});
        this->reg.add_component<Wave_pattern>(entity, Wave_pattern{1.f, 0.02f});
        break;
    }
    this->_networkSender->sendCreateEnemy(type, entity, position_x , position_y);
}

void GameLogique::runGame() {
    std::clock_t clock = std::clock();
    std::clock_t spawnClock = std::clock();
    while (1) {
        if (this->running) {
            if (static_cast<float>(std::clock() - clock) / CLOCKS_PER_SEC > 1 / frequency) {
                clock = std::clock();
                sys.wave_pattern_system(reg, static_cast<float>(clock) / CLOCKS_PER_SEC);
                sys.position_system(reg, this->_networkSender);     
            }
            if (static_cast<float>(std::clock() - spawnClock) / CLOCKS_PER_SEC > 2) {
                this->spawnEnnemy(0x03, 1000, 500);
                spawnClock = std::clock();
            }
        }
    }
}

void GameLogique::handleClientInput(std::pair<std::string, uint32_t> message)
{
    if (message.first.size() == 6) {
        std::cerr << "invalide player Input:" << std::endl;
        return;
    }

    size_t id = 0;
    char input = 0;
    memcpy(&id, &(message.first[1]), sizeof(size_t));
    input = message.first[5];

    auto &velocities = reg.get_components<Velocity_s>();
    if (velocities.size() <= id) {
        std::cerr << "Invalid entity ID: " << id << std::endl;
        return;
    }
    auto &velocitie = velocities[id];

    switch (input) {
        case 'x':
            // this->sys.shoot_system(reg, id, 0.1, true);
            break;
        case 'z':
            velocitie->y = -1;
            break;
        case 'q':
            velocitie->x = -1;
            break;
        case 's':
            velocitie->y = 1;
            break;
        case 'd':
            velocitie->x = 1;
            break;
        default:
            break;
    }
}

void GameLogique::handleRecieve()
{
    while (1)
    {
        if (network->hasMessages()) {
            std::pair<std::string, uint32_t> message = network->popMessage();
            std::cout << "message: " << (int)message.first[0] << std::endl;
            switch (message.first[0])
            {
            case 0x41:
                startGame();
                break;
            case 0x40:
                handleClientInput(message);
                break;
            default:
                std::cout << "unknowCommand" << std::endl;
                break;
            }
        }
    }
}
