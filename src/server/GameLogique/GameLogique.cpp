/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameLogique
*/

#include "GameLogique.hpp"

GameLogique::GameLogique(size_t port, int _frequency) {
    this->network                   = std::make_shared<NetworkLib::Server>(port);
    this->_networkSender            = std::make_unique<NetworkSender>(this->network);
    this->receiverThread            = std::thread(&GameLogique::handleRecieve, this);
    this->connectionManagmentThread = std::thread(&GameLogique::handleClientConnection, this);
    this->running                   = false;
    this->frequency                 = _frequency;
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
    this->reg.register_component<Direction>();
    this->reg.register_component<BossPatern>();

    try {
        std::string gameConfigPath = std::string("config") + PATH_SEPARATOR + std::string("R-Type")
                                     + PATH_SEPARATOR + std::string("game_config.cfg");
        _gameConfig.readFile(gameConfigPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                  << std::endl;
    }
    this->updateLevelConfig();
}

GameLogique::~GameLogique() {
    receiverThread.join();
    connectionManagmentThread.join();
}

void GameLogique::updateLevelConfig() {
    try {
        libconfig::Setting& levels  = this->_gameConfig.lookup("Menu.Game.level");
        std::string levelConfigPath = levels[this->_currentLevel].lookup("sceneConfig");
        size_t startPos             = 0;
        std::string from            = "/";
        while ((startPos = levelConfigPath.find(from, startPos)) != std::string::npos) {
            levelConfigPath.replace(startPos, from.length(), PATH_SEPARATOR);
            startPos += 2;
        }
        _levelConfig.readFile(levelConfigPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                  << std::endl;
    }
    assetEditorParsing.reset(new AssetEditorParsing(_levelConfig));
}

void GameLogique::startGame(int idEntity) {
    if (running == false) {
        for (size_t i = 0; i != network->getClientCount(); i++) {
            auto& pos = reg.get_components<Position>()[i];
            if (pos) {
                pos->x = 100.f;
                pos->y = 100 + (100.f * i);
            }
            this->_networkSender->sendPositionUpdate(i, 100.f, 100 + (100.f * i));
#ifdef _WIN32
            Sleep(10);
#else
            usleep(10000);
#endif
        }
#ifdef _WIN32
        Sleep(1);
#else
        sleep(1);
#endif
        this->_networkSender->sendStateChange(idEntity, 0x03);
        this->running = true;
    }
}

void GameLogique::spawnCustomEntity(char type, float position_x, float position_y, size_t entity) {
    std::shared_ptr<EntityData>& entityData = this->assetEditorParsing->getEntityData(type);
    if (entity == 1000000000) {
        entity = this->reg.spawn_entity();
    }

    this->reg.add_component<Position>(entity, Position{position_x, position_y});
    this->reg.add_component<Velocity>(entity, Velocity{0, 0});
    this->reg.add_component<Damage>(entity, Damage{20});
    if (entityData->health != nullptr) {
        this->reg.add_component<Health>(
            entity, Health{entityData->health->health, entityData->health->maxHealth, false, true});
    }
    if (entityData->playerFollowingPattern != nullptr) {
        this->reg.add_component<PlayerFollowingPattern>(
            entity, PlayerFollowingPattern{entityData->playerFollowingPattern->speed});
    }
    if (entityData->straightLinePattern != nullptr) {
        this->reg.add_component<StraightLinePattern>(
            entity, StraightLinePattern{entityData->straightLinePattern->speed});
    }
    if (entityData->shootPlayerPattern != nullptr) {
        this->reg.add_component<ShootPlayerPattern>(
            entity, ShootPlayerPattern{entityData->shootPlayerPattern->projectileSpeed,
                                       entityData->shootPlayerPattern->shootCooldown,
                                       entityData->shootPlayerPattern->lastShotTime});
    }
    if (entityData->shootStraightPattern != nullptr) {
        this->reg.add_component<ShootStraightPattern>(
            entity, ShootStraightPattern{2.0, 2.0, entityData->shootStraightPattern->lastShotTime});
    }
    if (entityData->WavePattern != nullptr) {
        this->reg.add_component<Wave_pattern>(entity, Wave_pattern{entityData->WavePattern->amplitude,
                                                                   entityData->WavePattern->frequency,
                                                                   std::chrono::steady_clock::now()});
    }
    if (entityData->size != nullptr) {
        this->reg.add_component<Size>(entity, Size{entityData->size->x, entityData->size->y});
    }
    this->reg.add_component<Type>(entity, Type{EntityType::ENEMY});
    this->reg.add_component<Direction>(entity, Direction{0, 0});
    this->_networkSender->sendCreateEnemy(type, entity, position_x, position_y);
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
            this->reg.add_component<ScoreValue>(entity, ScoreValue{10});
            break;
        case 0x04:
            this->reg.add_component<Position>(entity, Position{position_x, position_y});
            this->reg.add_component<Velocity>(entity, Velocity{-1, 0});
            this->reg.add_component<Health>(entity, Health{100, 100, false, true});
            this->reg.add_component<Damage>(entity, Damage{20});
            this->reg.add_component<Wave_pattern>(entity,
                                                  Wave_pattern{1.f, 0.02f, std::chrono::steady_clock::now()});
            this->reg.add_component<Size>(entity, Size{70, 71});
            this->reg.add_component<Type>(entity, Type{EntityType::ENEMY});
            this->reg.add_component<ScoreValue>(entity, ScoreValue{10});
            break;
        case 0x05:
            this->reg.add_component<Position>(entity, Position{position_x, position_y});
            this->reg.add_component<Velocity>(entity, Velocity{0, 0});
            this->reg.add_component<Health>(entity, Health{100, 100, false, true});
            this->reg.add_component<Damage>(entity, Damage{20});
            this->reg.add_component<PlayerFollowingPattern>(entity, PlayerFollowingPattern{0.5f});
            this->reg.add_component<Size>(entity, Size{70, 71});
            this->reg.add_component<Type>(entity, Type{EntityType::ENEMY});
            this->reg.add_component<ScoreValue>(entity, ScoreValue{10});
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
            this->reg.add_component<ScoreValue>(entity, ScoreValue{10});
            break;
        case 0x10:
            reg.add_component<Position>(entity, Position{position_x, position_y});
            reg.add_component<Tag>(entity, Tag{"boss"});
            reg.add_component<Health>(
                entity, Health{1000, 100, false, false}); // We can destroy the boss with a projectile
            reg.add_component<Damage>(entity, Damage{10});
            reg.add_component<Velocity>(entity, Velocity{0, 0});
            reg.add_component<Size>(entity, Size{325, 125});
            reg.add_component<Type>(entity, Type{EntityType::BOSS});
            reg.add_component<BossPatern>(
                entity, BossPatern{-1, true, false, 10.0, std::chrono::steady_clock::now()});
            reg.add_component<ScoreValue>(entity, ScoreValue{30});
            break;
        default:
            std::map<uint8_t, std::shared_ptr<EntityData>>& entities =
                this->assetEditorParsing->getEntities();

            std::vector<std::map<uint8_t, std::shared_ptr<EntityData>>::iterator> validEntities;
            std::vector<std::map<uint8_t, std::shared_ptr<EntityData>>::iterator> staticEntities;

            for (auto it = entities.begin(); it != entities.end(); ++it) {
                if (it->second->number != -1 && it->second->number != 0) {
                    validEntities.push_back(it);
                } else if (it->second->number == -1) {
                    staticEntities.push_back(it);
                }
            }

            if (!validEntities.empty()) {
                int randomIndex = std::rand() % validEntities.size();
                auto selectedIt = validEntities[randomIndex];
                this->spawnCustomEntity(selectedIt->first, position_x, position_y, entity);
                selectedIt->second->number -= 1;
            } else {
                bool enemyExists = false; // check if there is still an enemy
                for (auto& types : reg.get_components<Type>()) {
                    if (types && types->type == EntityType::ENEMY) {
                        enemyExists = true;
                        ennemyAlive = enemyExists;
                        break;
                    }
                }
                this->_networkSender->sendCreateEnemy(0x03, entity, position_x, position_y);

                if (!enemyExists) {
                    ennemyAlive = false;
                    return;
                }
            }
            for (auto& it : staticEntities) {
                if (it->second->pos != nullptr && it->second->pos->x < this->_camera_x) {
                    this->spawnCustomEntity(type, 1800, it->second->pos->y, 1000000000);
                    it->second->number = 0;
                }
            }
            return;
            break;
        }
        this->reg.add_component<Direction>(entity, Direction{0, 0});
        this->_networkSender->sendCreateEnemy(type, entity, position_x, position_y);
    }
}

void GameLogique::spawnWave() {
    spawnEnnemy(0x10, 1620, 500);
}

bool GameLogique::getfriendlyfire() {
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    cfg.readFile(configPath.c_str());
    std::string friendlyfireStr;
    const libconfig::Setting& root = cfg.getRoot();
    const libconfig::Setting& keys = root["Keys"];

    for (int i = 0; i < keys.getLength(); ++i) {
        const libconfig::Setting& key = keys[i];
        std::string name;
        key.lookupValue("name", name);
        if (name == "FRIENDLY FIRE") {
            key.lookupValue("value", friendlyfireStr);
            break;
        }
    }

    if (friendlyfireStr == "ON") return true;
    return false;
}

void GameLogique::runGame() {
    std::clock_t clock           = std::clock();
    std::clock_t spawnClock      = std::clock();
    int friendlyFireCheckCounter = 0;
    std::clock_t pingClock       = std::clock();

    while (1) {
        if (this->running) {
            if (friendlyFireCheckCounter == 0) {
                friendlyfire             = getfriendlyfire();
                friendlyFireCheckCounter = 999;
            }

            if (static_cast<float>(std::clock() - clock) / CLOCKS_PER_SEC > float(1) / float(frequency)) {
                clock = std::clock();
                sys.wave_pattern_system(reg, logger);
                sys.Straight_line_pattern_system(this->reg);
                sys.player_following_pattern_system(this->reg);
                sys.shoot_player_pattern_system(this->reg, this->_networkSender);
                sys.shoot_straight_pattern_system(this->reg, this->_networkSender);
                sys.collision_system(reg, std::make_pair<size_t, size_t>(1920, 1080), this->_networkSender,
                                     logger, friendlyfire);
                sys.position_system(reg, this->_networkSender, logger);
                sys.boss_system(reg, this->_networkSender);
                _camera_x += 0.1;
            }
            if (static_cast<float>(std::clock() - spawnClock) / CLOCKS_PER_SEC > 5) {
                this->spawnEnnemy(0x61, 1920, rand() % 700 + 200);
                spawnClock = std::clock();
            }
            if (static_cast<float>(std::clock() - pingClock) / CLOCKS_PER_SEC > 15) {
                sys.ping_client(reg, this->_networkSender);
                pingClock = std::clock();
            }
            if (this->areAllPlayersDead() == true) {
                this->clearGame();
#ifdef _WIN32
                Sleep(1);
#else
                sleep(1);
#endif
                this->_networkSender->sendStateChange(1, 0x04);
                this->running       = false;
                this->_currentLevel = 0;
                this->_networkSender->sendLevelUpdate(this->_currentLevel);
                this->updateLevelConfig();
                ennemyAlive = true;
            }

            if (ennemyAlive == false) {
                this->handleChangeLevel(_currentLevel + 1);
            }
        }
    }
}

void GameLogique::handleChangeLevel(unsigned int newLevel) {
    clearGame();
    ennemyAlive = true;
    try {
        libconfig::Setting& levels = this->_gameConfig.lookup("Menu.Game.level");
        if (newLevel >= (unsigned int)levels.getLength()) {
            this->running = false;
#ifdef _WIN32
            Sleep(1);
#else
            sleep(1);
#endif
            this->_networkSender->sendStateChange(1, 0x01);
            this->_currentLevel = 0;
            this->_networkSender->sendLevelUpdate(this->_currentLevel);
            this->updateLevelConfig();
            return;
        }
        this->_networkSender->sendLevelUpdate(newLevel);
        this->_currentLevel = newLevel;
        this->updateLevelConfig();
    } catch (std::exception& e) {
        std::cerr << "failed to load level" << std::endl;
    }
}

bool GameLogique::areAllPlayersDead() {
    bool anyPlayerDead = true;

    for (auto& player : reg.get_components<Type>()) {
        if (player && player->type == EntityType::PLAYER) {
            anyPlayerDead = false;
        }
    }
    return anyPlayerDead;
}

void GameLogique::clearGame() {
    auto& types = reg.get_components<Type>();

    for (size_t i = 0; i < types.size(); ++i) {
        auto& type = types[i];
#ifdef _WIN32
        Sleep(1);
#else
        usleep(1000);
#endif
        if (type) {
            this->_networkSender->sendDeleteEntity(i);
            this->reg.kill_entity(i);
        }
    }
#ifdef _WIN32
    Sleep(1);
#else
    usleep(1000);
#endif
    for (size_t numberPlayer = 0; numberPlayer != this->network->getClientCount(); numberPlayer++) {
        entity_t entity = this->reg.spawn_entity();
        this->reg.add_component<Position>(entity, Position_s{100.f + (100.f * numberPlayer), 100.f});
        this->reg.add_component<Velocity>(entity, Velocity_s{0.f, 0.f});
        this->reg.add_component<Tag>(entity, Tag{"player"});
        this->reg.add_component<Health>(entity, Health{100, 100, true, true});
        this->reg.add_component<Shoot>(entity, Shoot{true, std::chrono::steady_clock::now()});
        this->reg.add_component<ShootingSpeed_s>(entity, ShootingSpeed_s{0.3f});
        this->reg.add_component<Type>(entity, Type{EntityType::PLAYER});
        this->reg.add_component<Size>(entity, Size{130, 80});
        this->reg.add_component<Direction>(entity, Direction{0, 0});
        this->_networkSender->sendCreatePlayer(numberPlayer, 100.f, 100 + (100.f * numberPlayer));
        this->playersId[numberPlayer] = entity;
#ifdef _WIN32
        Sleep(1);
#else
        usleep(1000);
#endif
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
        std::cerr << "Invalid message size" << std::endl;
        return;
    }
    if (running == false) return;

    size_t id  = 0;
    char input = 0;
    memcpy(&id, &(message.first[1]), sizeof(int));
    input = message.first[5];

    auto& velocities = reg.get_components<Velocity_s>();
    auto& types      = reg.get_components<Type>();
    if ((unsigned int)velocities.size() <= this->playersId[message.second]
        && this->playersId[message.second] <= (unsigned int)types.size()) {
        std::cerr << "Invalid entity ID: " << this->playersId[message.second] << std::endl;
        return;
    }
    auto& velocitie = velocities[this->playersId[message.second]];
    auto& type      = types[this->playersId[message.second]];
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
            this->sys.shoot_system(reg, this->playersId[message.second], this->_networkSender, logger);
        }
    }
}

void GameLogique::handleRecieve() {
    while (1) {
        if (network->hasMessages()) {
            std::pair<std::string, uint32_t> message = network->popMessage();
            switch (message.first[0]) {
            case 0x41:
                startGame(this->playersId[message.second]);
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
                auto& playerHealth = reg.get_components<Health_s>()[message.second];
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
                auto& speed                           = reg.get_components<ShootingSpeed_s>();
                speed[message.second]->shooting_speed = value;
                break;
            }
            case 0x47: {
                int pos_x, pos_y;
                std::memcpy(&pos_x, &message.first[2], sizeof(int));
                std::memcpy(&pos_y, &message.first[6], sizeof(int));
                auto& position = reg.get_components<Position_s>()[message.second];
                position->x    = pos_x;
                position->y    = pos_y;
                _networkSender->sendPositionUpdate(message.second, pos_x, pos_y);
                break;
            }
            case 0x48: {
                int value;
                std::memcpy(&value, &message.first[1], sizeof(int));
                auto& playerHealth   = reg.get_components<Health_s>()[message.second];
                playerHealth->health = value;
                break;
            }
            default:
                std::cerr << "unknowCommand" << std::endl;
                break;
            }
        }
    }
}

void GameLogique::handleClientConnection() {
    while (1) {
        if (network->hasNewClientConnected()) {
            size_t clientId = network->popNewConnectedClient();
            {
                std::lock_guard<std::mutex> lock(this->_mutex);
                if (running == false) {
                    size_t entity = this->reg.spawn_entity();
                    this->reg.add_component<Position>(entity, Position_s{100.f + (100.f * clientId), 100.f});
                    this->reg.add_component<Velocity>(entity, Velocity_s{0.f, 0.f});
                    this->reg.add_component<Tag>(entity, Tag{"player"});
                    this->reg.add_component<Health>(entity, Health{100, 100, true, true});
                    this->reg.add_component<Shoot>(entity, Shoot{true, std::chrono::steady_clock::now()});
                    this->reg.add_component<ShootingSpeed_s>(entity, ShootingSpeed_s{0.3f});
                    this->reg.add_component<Type>(entity, Type{EntityType::PLAYER});
                    this->reg.add_component<Size>(entity, Size{130, 80});
                    this->reg.add_component<Direction>(entity, Direction{0, 0});
                    this->_networkSender->sendCreatePlayer(clientId, 100.f, 100 + (100.f * clientId));
                    this->playersId[clientId] = entity;
                }

                auto& positions = reg.get_components<Position_s>();
                auto& types     = reg.get_components<Type>();

                for (size_t i = 0; i < positions.size() && i < types.size(); ++i) {
                    auto& position = positions[i];
                    auto& type     = types[i];
                    if (type && position && (i != clientId || running)) {
                        switch (type->type) {
                        case EntityType::ENEMY:
                            this->_networkSender->sendCreateEnemy(0x03, i, position->x, position->y,
                                                                  clientId);
                            break;
                        case EntityType::BOSS:
                            this->_networkSender->sendCreateEnemy(0x10, i, position->x, position->y,
                                                                  clientId);
                            break;
                        case EntityType::PLAYER:
                            this->_networkSender->sendCreatePlayer(i, position->x, position->y, clientId);
                            break;
                        case EntityType::PLAYER_PROJECTILE:
                            this->_networkSender->sendCreateProjectil(i, position->x, position->y, 0,
                                                                      clientId);
                            break;
                        case EntityType::ENEMY_PROJECTILE:
                            this->_networkSender->sendCreateProjectil(i, position->x, position->y, 0,
                                                                      clientId);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
}
