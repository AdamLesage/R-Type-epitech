/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameLogique
*/

#include "GameLogique.hpp"

GameLogique::GameLogique(size_t port, int _frequency) {
    this->network        = std::make_shared<NetworkLib::Server>(port);
    this->_networkSender = std::make_unique<NetworkSender>(this->network);
    this->receiverThread = std::thread(&GameLogique::handleRecieve, this);
    this->running        = false;
    this->frequency      = _frequency;
    this->reg.register_component<Position>();
    this->reg.register_component<Velocity>();
    this->reg.register_component<Tag>();
    this->reg.register_component<Health>();
    this->reg.register_component<Damage>();
    this->reg.register_component<Wave_pattern>();
    this->reg.register_component<Shoot>();
    this->reg.register_component<ShootingSpeed>();
    this->reg.register_component<Type>();
    this->reg.register_component<StraightLinePattern>();
    this->reg.register_component<PlayerFollowingPattern>();
    this->reg.register_component<ShootPlayerPattern>();
    this->reg.register_component<ShootStraightPattern>();
    this->reg.register_component<Size>();
}

GameLogique::~GameLogique() {
    receiverThread.join();
}

void GameLogique::startGame() {
    if (running == false) {
        // std::cout << network->getClientCount() << std::endl;
        for (size_t i = 0; i != network->getClientCount(); i++) {
            size_t entity = this->reg.spawn_entity();
            float xPos    = 100.f + (100.f * i);
            float yPos    = 100.f;
            this->reg.add_component<Position>(entity, Position_s{100.f + (100.f * i), 100.f});
            this->reg.add_component<Velocity>(entity, Velocity_s{0.f, 0.f});
            this->reg.add_component<Tag>(entity, Tag{"player"});
            this->reg.add_component<Health>(entity, Health{100, 100, true, true});
            this->reg.add_component<Shoot>(entity, Shoot{true, std::chrono::steady_clock::now()});
            this->reg.add_component<ShootingSpeed_s>(entity, ShootingSpeed_s{0.3f});
            this->reg.add_component<Type>(entity, Type{EntityType::PLAYER});
            this->reg.add_component<Size>(entity, Size{130, 80});
            this->_networkSender->sendCreatePlayer(entity, xPos, yPos);
        }
        this->running = true;
    }
}

void GameLogique::spawnEnnemy(char type, float position_x, float position_y) {
    {
        std::lock_guard<std::mutex> lock(this->_mutex);

        size_t entity = this->reg.spawn_entity();

        switch (type) {
        case 0x03:
            this->reg.add_component<Position>(entity, Position{position_x, position_y});
            this->reg.add_component<Velocity>(entity, Velocity{0, 0});
            this->reg.add_component<Health>(entity, Health{50, 50, false, true});
            this->reg.add_component<Damage>(entity, Damage{20});
            this->reg.add_component<StraightLinePattern>(entity, StraightLinePattern{-1});
            this->reg.add_component<ShootStraightPattern>(
                entity, ShootStraightPattern{2.0, 2.0, std::chrono::steady_clock::now()});
            this->reg.add_component<Size>(entity, Size{70, 71});
            this->reg.add_component<Type>(entity, Type{EntityType::ENEMY});
            break;
        case 0x04:
            this->reg.add_component<Position>(entity, Position{position_x, position_y});
            this->reg.add_component<Velocity>(entity, Velocity{-1, 0});
            this->reg.add_component<Health>(entity, Health{100, 100, false, true});
            this->reg.add_component<Damage>(entity, Damage{20});
            this->reg.add_component<Wave_pattern>(entity, Wave_pattern{1.f, 0.02f});
            this->reg.add_component<Size>(entity, Size{70, 71});
            this->reg.add_component<Type>(entity, Type{EntityType::ENEMY});
            break;
        case 0x05:
            this->reg.add_component<Position>(entity, Position{position_x, position_y});
            this->reg.add_component<Velocity>(entity, Velocity{0, 0});
            this->reg.add_component<Health>(entity, Health{100, 100, false, true});
            this->reg.add_component<Damage>(entity, Damage{20});
            this->reg.add_component<PlayerFollowingPattern>(entity, PlayerFollowingPattern{0.5f});
            this->reg.add_component<Size>(entity, Size{70, 71});
            this->reg.add_component<Type>(entity, Type{EntityType::ENEMY});
            break;
        case 0x06:
            this->reg.add_component<Position>(entity, Position{position_x, position_y});
            this->reg.add_component<Velocity>(entity, Velocity{0, 0});
            this->reg.add_component<Health>(entity, Health{100, 100, false, true});
            this->reg.add_component<Damage>(entity, Damage{20});
            this->reg.add_component<ShootPlayerPattern>(
                entity, ShootPlayerPattern{2, 5, std::chrono::steady_clock::now()});
            this->reg.add_component<Size>(entity, Size{70, 71});
            this->reg.add_component<Type>(entity, Type{EntityType::ENEMY});
            break;
        default:
            this->reg.add_component<Position>(entity, Position{position_x, position_y});
            this->reg.add_component<Velocity>(entity, Velocity{0, 0});
            this->reg.add_component<Health>(entity, Health{100, 100, false, true});
            this->reg.add_component<Damage>(entity, Damage{20});
            this->reg.add_component<StraightLinePattern>(entity, {0.5f});
            this->reg.add_component<Size>(entity, Size{70, 71});
            this->reg.add_component<Type>(entity, Type{EntityType::ENEMY});
            break;
        }
        this->_networkSender->sendCreateEnemy(type, entity, position_x, position_y);
    }
}

void GameLogique::spawnWave()
{
    spawnEnnemy(0x03, 1920, 10);
    spawnEnnemy(0x03, 1920, 160);
    spawnEnnemy(0x03, 1920, 360);
    spawnEnnemy(0x03, 1920, 580);
    spawnEnnemy(0x03, 1920, 920);
}

void GameLogique::runGame() {
    std::clock_t clock      = std::clock();
    std::clock_t spawnClock = std::clock();
    while (1) {
        if (this->running) {
            if (static_cast<float>(std::clock() - clock) / CLOCKS_PER_SEC > float(1) / float(frequency)) {
                clock = std::clock();
                sys.wave_pattern_system(reg, static_cast<float>(clock) / CLOCKS_PER_SEC, logger);
                sys.Straight_line_pattern_system(this->reg);
                sys.player_following_pattern_system(this->reg);
                sys.shoot_player_pattern_system(this->reg, this->_networkSender);
                sys.shoot_straight_pattern_system(this->reg, this->_networkSender);
                sys.collision_system(reg, std::make_pair<size_t, size_t>(1920, 1080), this->_networkSender,
                                     logger);
                sys.position_system(reg, this->_networkSender, logger);
            }
            if (static_cast<float>(std::clock() - spawnClock) / CLOCKS_PER_SEC > 5) {
                this->spawnEnnemy(0x03, 1920, rand() % 700 + 200);
                spawnClock = std::clock();
            }
        }
    }
}

std::array<char, 6> GameLogique::retrieveInputKeys() {
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    cfg.readFile(configPath.c_str());
    std::string keyStr;
    std::array<char, 6> inputKeys;
    const libconfig::Setting& root = cfg.getRoot();
    const libconfig::Setting& keys = root["Keys"];

    // Map to associate key names with their respective index in the array
    std::unordered_map<std::string, int> keyMap = {{"up", 0},    {"down", 1},  {"left", 2},
                                                   {"right", 3}, {"shoot", 4}, {"settings", 5}};

    for (int i = 0; i < keys.getLength(); ++i) {
        const libconfig::Setting& key = keys[i];
        std::string name;
        key.lookupValue("name", name);
        auto it = keyMap.find(name);

        // If the key name is found in the map, assign the value
        if (it != keyMap.end()) {
            key.lookupValue("value", keyStr);
            inputKeys[it->second] = keyStr[0];
        }
    }
    return inputKeys;
}

void GameLogique::handleClientInput(std::pair<std::string, uint32_t> message) {
    if (message.first.size() != 6) {
        std::cout << "Invalid message size" << std::endl;
        return;
    }

    size_t id  = 0;
    char input = 0;
    memcpy(&id, &(message.first[1]), sizeof(int));
    input = message.first[5];

    auto& velocities = reg.get_components<Velocity_s>();
    auto& types      = reg.get_components<Type>();
    if ((unsigned int)velocities.size() <= message.second && message.second <= (unsigned int)types.size()) {
        std::cerr << "Invalid entity ID: " << message.second << std::endl;
        return;
    }
    auto& velocitie = velocities[message.second];
    auto& type      = types[message.second];
    if (type->type != EntityType::PLAYER) {
        return;
    }
    std::array<char, 6> keys = retrieveInputKeys();

    if (input == keys[0]) { // UP
        velocitie->y = -2;
    } else if (input == keys[1]) { // DOWN
        velocitie->y = 2;
    } else if (input == keys[2]) { // RIGHT
        velocitie->x = 2;
    } else if (input == keys[3]) { // LEFT
        velocitie->x = -2;
    } else if (input == keys[4]) { // SHOOT
        {
            std::lock_guard<std::mutex> lock(this->_mutex);
            this->sys.shoot_system(reg, message.second, this->_networkSender, logger);
        }
    }
}

void GameLogique::handleRecieve() {
    while (1) {
        if (network->hasMessages()) {
            std::pair<std::string, uint32_t> message = network->popMessage();
            switch (message.first[0]) {
            case 0x41:
                startGame();
                break;
            case 0x40:
                handleClientInput(message);
                break;
            case 0x42: {
                int pos_x, pos_y;
                std::memcpy(&pos_x, &message.first[2], sizeof(int));
                std::memcpy(&pos_y, &message.first[6], sizeof(int));
                spawnEnnemy(message.first[1], static_cast<float>(pos_x), static_cast<float>(pos_y));
                break;
            }
            case 0x43: {
                int entityId;
                std::memcpy(&entityId, &message.first[1], sizeof(int));
                entity_t entity = reg.entity_from_index(entityId);
                reg.kill_entity(entity);
                _networkSender->sendDeleteEntity(entityId);
                break;
            }
            case 0x44: {
                spawnWave();
                break;
            }
            case 0x45: {
                auto &playerHealth = reg.get_components<Health_s>()[message.second];
                if (message.first[1] == 0x01) {
                    playerHealth->isDamageable = false;
                }
                if (message.first[1] == 0x02) {
                    playerHealth->isDamageable = true;
                }
                break;
            }
            case 0x46: {
                float value;
                std::memcpy(&value, &message.first[1], sizeof(float));
                auto& speed  = reg.get_components<ShootingSpeed_s>();
                speed[message.second]->shooting_speed = value;
                break;
            }
            case 0x47: {
                int pos_x, pos_y;
                std::memcpy(&pos_x, &message.first[2], sizeof(int));
                std::memcpy(&pos_y, &message.first[6], sizeof(int));
                auto& position  = reg.get_components<Position_s>()[message.second];
                position->x = pos_x;
                position->y = pos_y;
                _networkSender->sendPositionUpdate(message.second, pos_x, pos_y);
                break;
            }
            case 0x48: {
                int value;
                std::memcpy(&value, &message.first[1], sizeof(int));
                auto &playerHealth = reg.get_components<Health_s>()[message.second];
                playerHealth->health = value;
                
                break;
            }
            default:
                std::cout << "unknowCommand" << std::endl;
                break;
            }
        }
    }
}
