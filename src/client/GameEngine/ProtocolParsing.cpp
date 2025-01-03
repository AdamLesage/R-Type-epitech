/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ProtocolParsing
*/

#include "ProtocolParsing.hpp"

RType::ProtocolParsing::ProtocolParsing(std::string protocolPath, Registry& registry, std::shared_ptr<std::mutex> mutex) : _registry(registry) {
    try {
        _protocolPath = protocolPath;
        _cfg.readFile(_protocolPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        throw std::runtime_error("I/O error while reading file.");
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                  << std::endl;
        throw std::runtime_error("Parse error");
    }

    _messageTypeMap = {{"PLAYER_CREATION", {0x01, "player_creation"}},
                       {"PROJECTILE_CREATION", {0x02, "projectile_creation"}},
                       {"ENEMY_CREATION", {0x03, "enemy_creation"}},
                        {"MISSILE_CREATION", {0x04, "missile_creation"}},
                        {"BIG_MISSILE_CREATION", {0x05, "big_missile_creation"}},
                       {"BOSS_CREATION", {0x10, "boss_creation"}},
                       {"SHIELD_CREATION", {0x21, "shield_creation"}},
                       {"MACHINEGUN_CREATION", {0x22, "machinegun_creation"}},
                        {"ROCKET_CREATION", {0x23, "rocket_creation"}},
                       {"BEAM_CREATION", {0x24, "beam_creation"}},
                       {"CLONE_CREATION", {0x25, "beam_creation"}},
                       {"WALL_CREATION", {0x26, "wall_creation"}},
                       {"REWARD_CREATION", {0x27, "reward_creation"}},
                       {"ENTITY_DELETION", {0x29, "entity_deletion"}},
                       {"POSITION_UPDATE", {0x30, "position_update"}},
                       {"HEALTH_UPDATE", {0x31, "health_update"}},
                       {"DIRECTION_UPDATE", {0x32, "direction_update"}},
                       {"OBJECT_COLLECTION", {0x33, "object_collection"}},
                       {"PROJECTILE_FIRING", {0x34, "projectile_firing"}},
                       {"PROJECTILE_COLLISION", {0x35, "projectile_collision"}},
                       {"SCORE_UPDATE", {0x36, "score_update"}},
                       {"STATE_CHANGE", {0x37, "state_change"}},
                       {"LEVEL_UPDATE", {0x3a, "level_update"}},
                       {"PING_CLIENT", {0x99, "ping_client"}},
                       {"SHOOT_SOUND", {0x98, "shoot_sound"}}};
    _mutex = mutex;
}

RType::ProtocolParsing::~ProtocolParsing() {
}

int RType::ProtocolParsing::updateIndexFromBinaryData(const std::string& message, int& index) {
    int totalSize = 0;

    try {
        totalSize = _cfg.lookup("protocol").lookup(message).lookup("total_size");
    } catch (const libconfig::SettingNotFoundException& nfex) {
        std::cerr << "Setting not found: " << nfex.getPath() << std::endl;
        return false;
    } catch (const libconfig::SettingTypeException& stex) {
        std::cerr << "Setting type error: " << stex.getPath() << std::endl;
        return false;
    }
    index += totalSize;
    return index;
}

bool RType::ProtocolParsing::checkMessageType(const std::string& messageType,
                                              const std::string& message,
                                              int& index) {
    // Check if message is for the current parsing function such as current type (0xXX) is correct
    if (_messageTypeMap.find(messageType) != _messageTypeMap.end()) {
        if (static_cast<uint8_t>(message[index]) != _messageTypeMap[messageType].first) return false;
    } else {
        return false;
    }
    // Check if the message type is a byte
    if (sizeof(message[index]) != sizeof(uint8_t)) return false;
    // Compare message size with the expected size in the protocol config file
    if (!_cfg.exists("protocol")) {
        return false;
    }
    auto& protocol = _cfg.lookup("protocol");
    if (!protocol.exists(_messageTypeMap[messageType].second)) {
        return false;
    }
    auto& element = protocol.lookup(_messageTypeMap[messageType].second);
    if (!element.exists("total_size")) {
        return false;
    }
    try {
        int totalSize = element.lookup("total_size");
        if (index < 0 || index >= static_cast<int>(message.length()) ||
            static_cast<int>(message.length()) - index < totalSize) {
            return false;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: unable to convert total_size to integer" << std::endl;
        return false;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: total_size value is too large" << std::endl;
        return false;
    }
    return true;
}

bool RType::ProtocolParsing::parsePlayerCreation(const std::string& message, int& index) {
    if (!checkMessageType("PLAYER_CREATION", message, index)) return false;

    unsigned int playerId = 0;
    float posX;
    float posY;

    try {
        std::memcpy(&playerId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the player creation message" << std::endl;
        return false;
    }

    try {
        {
            std::lock_guard<std::mutex> lock(*this->_mutex.get());
            entity_t entity = _registry.spawn_entity();
            _registry.add_component<Position>(entity, Position{posX, posY});
            _registry.add_component<Tag>(entity, Tag{"player"});
            _registry.add_component<Controllable>(entity, Controllable{true, false, false, false, false});
            _registry.add_component<Scale>(entity, Scale{1});
            _registry.add_component<Health>(entity, Health{100, 100, true, true});
            _registry.add_component<Shoot>(entity, Shoot{true, std::chrono::steady_clock::now()});
            _registry.add_component<ShootingSpeed>(entity, ShootingSpeed{0.5});
            _registry.add_component<Damage>(entity, Damage{10});
            _registry.add_component<Level>(entity, Level{1});
            _registry.add_component<Rotation>(entity, Rotation{0});
            _registry.add_component<Velocity>(entity, Velocity{0, 0});
            _registry.add_component<Size>(entity, Size{130, 80});
            _registry.add_component<Type>(entity, Type{EntityType::PLAYER});
            _registry.add_component<Direction>(entity, Direction{1, 0});
            if (playerId <= 5)
                playerId = 0;
            std::string path = std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + "player_"
                            + std::to_string(playerId + 1) + ".png";
            _registry.add_component<Sprite>(entity, Sprite{path, {263, 116}, {0, 0}});

        }
        this->updateIndexFromBinaryData("player_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the player" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseEntityCreation(const std::string& message, int& index) {

    if (message.length() - index < 13) {
        return false;
    }
    std::shared_ptr<EntityData> &data = _assetEditorParsing->getEntityData(message[index]);
    if (data == nullptr) {
        return false;
    }
    unsigned int entityId;
    float posX;
    float posY;

    try {
        std::memcpy(&entityId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the player creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        if (data->pos != nullptr) {
            _registry.add_component<Position>(entity, Position{posX, posY});
        }
        if (data->size != nullptr) {
            _registry.add_component<Size>(entity, Size{data->size->x, data->size->y});
        }
        if (data->sprite != nullptr) {
            _registry.add_component<Sprite>(entity, Sprite{data->sprite->spritePath, {data->sprite->rectSize[0], data->sprite->rectSize[1]}, {data->sprite->rectPos[0], data->sprite->rectPos[1]}});
        }
        if (data->rotation != nullptr) {
            _registry.add_component<Rotation>(entity, Rotation{data->rotation->rotation});
        }
        if (data->annimation != nullptr) {
            _registry.add_component<Annimation>(entity, Annimation{data->annimation->annimationSpeed ,data->annimation->annimation, 0, std::chrono::steady_clock::now()});
        }
        if (data->type != nullptr) {
            _registry.add_component<Type>(entity, Type{data->type->type});
        }
        _registry.add_component<Direction>(entity, Direction{-1, 0});
        if (data->health != nullptr) {
            _registry.add_component<Health>(entity, Health{data->health->health, data->health->health, false, true});
        }

        this->updateIndexFromBinaryData("enemy_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the player" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseProjectileCreation(const std::string& message, int& index) {
    if (!checkMessageType("PROJECTILE_CREATION", message, index)) return false;

    unsigned int projectileId;
    float posX;
    float posY;
    unsigned int parentId;

    try {
        std::memcpy(&projectileId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
        std::memcpy(&parentId, &message[index + 13], sizeof(unsigned int));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the projectile creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"projectile"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Damage>(entity, Damage{10});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Size>(entity, Size{70, 30});
        _registry.add_component<Direction>(entity, Direction{0, 0});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});

        std::string path;
        auto parentTag = _registry.get_components<Tag>()[projectileId];
        if (parentTag.has_value() && parentTag.value().tag == "enemy") {
            path = std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_ennemy.png";
        }
        if (parentTag.has_value() && parentTag.value().tag == "player") {
            path = std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + PATH_SEPARATOR + "missile_" + std::to_string(parentId + 1) + ".png";
        }
        else {
            path = std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "missile_ennemy.png";
        }

        _registry.add_component<Sprite>(entity, Sprite{path, {71, 32}, {0, 0}});
        this->updateIndexFromBinaryData("projectile_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the projectile" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseMissileCreation(const std::string& message, int& index) {
    if (!checkMessageType("MISSILE_CREATION", message, index)) return false;

    unsigned int projectileId;
    float posX;
    float posY;

    try {
        std::memcpy(&projectileId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the projectile creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"projectile"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Damage>(entity, Damage{10});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Size>(entity, Size{70, 30});
        _registry.add_component<Direction>(entity, Direction{0, 0});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});

        std::string path = std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + "rocket_player.png";
        _registry.add_component<Sprite>(entity, Sprite{path, {165, 66}, {0, 0}});
        this->updateIndexFromBinaryData("missile_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the projectile" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseBigMissileCreation(const std::string& message, int& index) {
    if (!checkMessageType("BIG_MISSILE_CREATION", message, index)) return false;

    unsigned int projectileId;
    float posX;
    float posY;
    unsigned int parentId;

    try {
        std::memcpy(&projectileId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
        std::memcpy(&parentId, &message[index + 13], sizeof(unsigned int));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the projectile creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"projectile"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Damage>(entity, Damage{10});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Size>(entity, Size{240, 160});
        _registry.add_component<Direction>(entity, Direction{0, 0});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});

        std::string path;
        auto parentTag = _registry.get_components<Tag>()[projectileId];
        if (parentTag.has_value() && parentTag.value().tag == "player") {
            path = std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + PATH_SEPARATOR + "big_missile_" + std::to_string(parentId + 1) + ".png";
        } else {
            path = std::string("assets") + PATH_SEPARATOR + "bullet" + PATH_SEPARATOR + PATH_SEPARATOR + "big_missile_1.png";
        }
        _registry.add_component<Sprite>(entity, Sprite{path, {74, 52}, {0, 0}});
        std::vector<std::array<int, 4>> annimation = {{0, 0, 74, 52}, {74, 0, 74, 52}, 
                                                    {148, 0, 74, 52}, {222, 0, 74, 52}, 
                                                    {296, 0, 74, 52}, {370, 0, 74, 52}};
        _registry.add_component<Annimation>(entity, Annimation{0.1, annimation, 0, std::chrono::steady_clock::now()});
        this->updateIndexFromBinaryData("big_missile_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the projectile" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseEnemyCreation(const std::string& message, int& index) {
    if (!checkMessageType("ENEMY_CREATION", message, index)) return false;

    unsigned int enemyId;
    float posX;
    float posY;

    try {
        std::memcpy(&enemyId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the enemy creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"enemy"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Health>(entity, Health{100, 100, true, true});
        _registry.add_component<Damage>(entity, Damage{10});
        _registry.add_component<Level>(entity, Level{1});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Size>(entity, Size{70, 71});
        _registry.add_component<Direction>(entity, Direction{-1, 0});
        std::string path = std::string("assets") + PATH_SEPARATOR + "ennemy" + PATH_SEPARATOR + "enemy_2.png";
        _registry.add_component<Sprite>(entity, Sprite{path, {33, 36}, {0, 0}});
        this->updateIndexFromBinaryData("enemy_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the enemy" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseShieldCreation(const std::string& message, int& index) {
    if (!checkMessageType("SHIELD_CREATION", message, index)) return false;
    unsigned int bonusId;
    float posX;
    float posY;
    std::string path;

    try {
        std::memcpy(&bonusId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));

    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the bonus creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Direction>(entity, Direction{1, 0});
        _registry.add_component<Size>(entity, Size{70, 30});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Tag>(entity, Tag{"bonus"});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});
        path = std::string("assets") + PATH_SEPARATOR + "bonus" + PATH_SEPARATOR + "shield_bonus.png";
        _registry.add_component<Sprite>(entity, Sprite{path, {35, 30}, {0, 0}});
        this->updateIndexFromBinaryData("shield_creation", index);
        std::vector<std::array<int, 4>> annimation = {{0, 0, 32, 32}, {32, 0, 32, 32}, 
                                                    {64, 0, 32, 32}, {96, 0, 32, 32}, 
                                                    {128, 0, 32, 32}, {160, 0, 32, 32},
                                                    {192, 0, 32, 32}, {224, 0, 32, 32}, 
                                                    {256, 0, 32, 32}, {288, 0, 32, 32},
                                                    {320, 0, 32, 32}, {352, 0, 32, 32},
                                                    {384, 0, 32, 32}, {416, 0, 32, 32},
                                                    {448, 0, 32, 32}};
        _registry.add_component<Annimation>(entity, Annimation{0.1, annimation, 0, std::chrono::steady_clock::now()});
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the bonus" << std::endl;
        return false;
    }
    return true;
}

bool RType::ProtocolParsing::parseBossCreation(const std::string& message, int& index) {
    if (!checkMessageType("BOSS_CREATION", message, index)) return false;

    unsigned int bossId;
    float posX;
    float posY;

    try {
        std::memcpy(&bossId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the boss creation message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"boss"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Health>(entity, Health{100, 100, false, false}); // We can destroy the boss with a projectile
        _registry.add_component<Damage>(entity, Damage{10});
        _registry.add_component<Level>(entity, Level{1});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Size>(entity, Size{325, 125});
        _registry.add_component<Direction>(entity, Direction{-1, 0});
        std::string path = std::string("assets") + PATH_SEPARATOR + "ennemy" + PATH_SEPARATOR + "boss" + PATH_SEPARATOR + "boss_2.png";
        _registry.add_component<Sprite>(entity, Sprite{path, {1300, 500}, {0, 0}});
        this->updateIndexFromBinaryData("boss_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the boss" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseMachinegunCreation(const std::string& message, int& index) {
    if (!checkMessageType("MACHINEGUN_CREATION", message, index)) return false;
    unsigned int bonusId;
    float posX;
    float posY;
    std::string path;

    try {
        std::memcpy(&bonusId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));

    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the bonus creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Direction>(entity, Direction{1, 0});
        _registry.add_component<Size>(entity, Size{70, 30});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Tag>(entity, Tag{"bonus"});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});
        path = std::string("assets") + PATH_SEPARATOR + "bonus" + PATH_SEPARATOR + "machinegun_bonus.png";
        _registry.add_component<Sprite>(entity, Sprite{path, {35, 30}, {0, 0}});
        std::vector<std::array<int, 4>> annimation = {{0, 0, 32, 32}, {32, 0, 32, 32}, 
                                                    {64, 0, 32, 32}, {96, 0, 32, 32}, 
                                                    {128, 0, 32, 32}, {160, 0, 32, 32},
                                                    {192, 0, 32, 32}, {224, 0, 32, 32}, 
                                                    {256, 0, 32, 32}, {288, 0, 32, 32},
                                                    {320, 0, 32, 32}, {352, 0, 32, 32},
                                                    {384, 0, 32, 32}, {416, 0, 32, 32},
                                                    {448, 0, 32, 32}};
        _registry.add_component<Annimation>(entity, Annimation{0.1, annimation, 0, std::chrono::steady_clock::now()});
        this->updateIndexFromBinaryData("machinegun_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the bonus" << std::endl;
        return false;
    }
    return true;
}

bool RType::ProtocolParsing::parseRocketCreation(const std::string& message, int& index) {
    if (!checkMessageType("ROCKET_CREATION", message, index)) return false;
    unsigned int bonusId;
    float posX;
    float posY;
    std::string path;

    try {
        std::memcpy(&bonusId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));

    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the bonus creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Direction>(entity, Direction{1, 0});
        _registry.add_component<Size>(entity, Size{70, 30});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Tag>(entity, Tag{"bonus"});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});
        path = std::string("assets") + PATH_SEPARATOR + "bonus" + PATH_SEPARATOR + "rocket_bonus.png";
        _registry.add_component<Sprite>(entity, Sprite{path, {35, 30}, {0, 0}});
        std::vector<std::array<int, 4>> annimation = {{0, 0, 32, 32}, {32, 0, 32, 32}, 
                                                    {64, 0, 32, 32}, {96, 0, 32, 32}, 
                                                    {128, 0, 32, 32}, {160, 0, 32, 32},
                                                    {192, 0, 32, 32}, {224, 0, 32, 32}, 
                                                    {256, 0, 32, 32}, {288, 0, 32, 32},
                                                    {320, 0, 32, 32}, {352, 0, 32, 32},
                                                    {384, 0, 32, 32}, {416, 0, 32, 32},
                                                    {448, 0, 32, 32}};
        _registry.add_component<Annimation>(entity, Annimation{0.1, annimation, 0, std::chrono::steady_clock::now()});
        this->updateIndexFromBinaryData("rocket_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the bonus" << std::endl;
        return false;
    }
    return true;
}

bool RType::ProtocolParsing::parseBeamCreation(const std::string& message, int& index) {
    if (!checkMessageType("BEAM_CREATION", message, index)) return false;
    unsigned int bonusId;
    float posX;
    float posY;
    std::string path;

    try {
        std::memcpy(&bonusId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));

    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the bonus creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Direction>(entity, Direction{1, 0});
        _registry.add_component<Size>(entity, Size{70, 30});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Tag>(entity, Tag{"bonus"});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});
        path = std::string("assets") + PATH_SEPARATOR + "bonus" + PATH_SEPARATOR + "beam_bonus.png";
        _registry.add_component<Sprite>(entity, Sprite{path, {35, 30}, {0, 0}});
        std::vector<std::array<int, 4>> annimation = {{0, 0, 32, 32}, {32, 0, 32, 32}, 
                                                    {64, 0, 32, 32}, {96, 0, 32, 32}, 
                                                    {128, 0, 32, 32}, {160, 0, 32, 32},
                                                    {192, 0, 32, 32}, {224, 0, 32, 32}, 
                                                    {256, 0, 32, 32}, {288, 0, 32, 32},
                                                    {320, 0, 32, 32}, {352, 0, 32, 32},
                                                    {384, 0, 32, 32}, {416, 0, 32, 32},
                                                    {448, 0, 32, 32}};
        _registry.add_component<Annimation>(entity, Annimation{0.1, annimation, 0, std::chrono::steady_clock::now()});
        this->updateIndexFromBinaryData("beam_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the bonus" << std::endl;
        return false;
    }
    return true;
}

bool RType::ProtocolParsing::parseCloneCreation(const std::string& message, int& index) {
    if (!checkMessageType("CLONE_CREATION", message, index)) return false;
    unsigned int bonusId;
    float posX;
    float posY;

    try {
        std::memcpy(&bonusId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));

    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the bonus creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Direction>(entity, Direction{1, 0});
        _registry.add_component<Size>(entity, Size{70, 30});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Tag>(entity, Tag{"bonus"});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});
        std::string path = std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR + std::string("bot_friend.png");
        _registry.add_component<Sprite>(entity, Sprite{path, {263, 116}, {0, 0}});
        this->updateIndexFromBinaryData("beam_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the bonus" << std::endl;
        return false;
    }
    return true;
}

bool RType::ProtocolParsing::parseWallCreation(const std::string& message, int& index) {
    if (!checkMessageType("WALL_CREATION", message, index)) return false;

    unsigned int wallId;
    float posX;
    float posY;
    float width;
    float height;

    try {
        std::memcpy(&wallId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
        std::memcpy(&width, &message[index + 13], sizeof(float));
        std::memcpy(&height, &message[index + 17], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the wall creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"wall"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Health>(
            entity, Health{100, 100, false, false}); // We can destroy the wall with a projectile
        this->updateIndexFromBinaryData("wall_creation", index);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the wall" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseRewardCreation(const std::string& message, int& index) {
    if (!checkMessageType("REWARD_CREATION", message, index)) return false;

    unsigned int rewardId;
    float posX;
    float posY;
    float width;
    float height;

    try {
        std::memcpy(&rewardId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
        std::memcpy(&width, &message[index + 13], sizeof(float));
        std::memcpy(&height, &message[index + 17], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the reward creation message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        this->updateIndexFromBinaryData("reward_creation", index);
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"reward"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Health>(entity, Health{0, 0, false, true});
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while creating the reward" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseEntityDeletion(const std::string& message, int& index) {
    if (!checkMessageType("ENTITY_DELETION", message, index)) return false;

    int entityId;

    try {
        std::memcpy(&entityId, &message[index + 1], sizeof(int));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the entity deletion message" << std::endl;
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        this->updateIndexFromBinaryData("entity_deletion", index);
        entity_t entity = _registry.entity_from_index(entityId);
        _registry.kill_entity(entity);
    } catch (const std::out_of_range& e) {
        std::cerr << "Entity not found for deletion" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while deleting the entity" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parsePositionUpdate(const std::string& message, int& index) {
    if (!checkMessageType("POSITION_UPDATE", message, index)) return false;

    unsigned int entityId;
    float posX;
    float posY;

    try {
        std::memcpy(&entityId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the position update message" << std::endl;
        return false;
    }

    try {
        this->updateIndexFromBinaryData("position_update", index);
        entity_t entity = _registry.entity_from_index(entityId);

        // Check if the entity has a position component
        auto optionalPositionComponent = _registry.get_components<Position>()[entity];
        if (optionalPositionComponent.has_value()
            == false) { // If the entity doesn't have a position component, add it
            _registry.add_component<Position>(entity, Position{posX, posY});
            return true;
        }

        // Remove the old position component and add the new one to update the position
        _registry.remove_component<Position>(entity);
        _registry.add_component<Position>(entity, Position{posX, posY});
    } catch (const std::out_of_range& e) {
        std::cerr << "Entity not found for position update" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating the position" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseHealthUpdate(const std::string& message, int& index) {
    if (!checkMessageType("HEALTH_UPDATE", message, index)) return false;

    unsigned int entityId;
    unsigned int health;

    try {
        std::memcpy(&entityId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&health, &message[index + 5], sizeof(unsigned int));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the health update message" << std::endl;
        return false;
    }

    try {
        this->updateIndexFromBinaryData("health_update", index);
        entity_t entity              = _registry.entity_from_index(entityId);
        auto optionalHealthComponent = _registry.get_components<Health>()[entity];

        // Check if the entity has a health component
        if (optionalHealthComponent.has_value()) {
            Health& healthComponent = optionalHealthComponent.value();
            // Remove the old health component and add the new one to update the health
            _registry.remove_component<Health>(entity);
            _registry.add_component<Health>(entity, Health{health, healthComponent.maxHealth,
                                                           healthComponent.isRegenerating,
                                                           healthComponent.isDamageable});
        } else {
            _registry.add_component<Health>(entity, Health{health, 100, true, true});
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "Entity not found for health update" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating the health" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseDirectionUpdate(const std::string& message, int& index) {
    if (!checkMessageType("DIRECTION_UPDATE", message, index)) return false;

    unsigned int entityId;
    float directionX;
    float directionY;

    try {
        std::memcpy(&entityId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&directionX, &message[index + 5], sizeof(float));
        std::memcpy(&directionY, &message[index + 9], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the direction update message" << std::endl;
        return false;
    }

    try {
        this->updateIndexFromBinaryData("direction_update", index);
        entity_t entity                 = _registry.entity_from_index(entityId);
        auto optionalDirectionComponent = _registry.get_components<Direction>()[entity];

        // Check if the entity has a direction component
        if (optionalDirectionComponent.has_value()) {
            Direction& directionComponent = optionalDirectionComponent.value();
            (void)directionComponent;
            // Remove the old direction component and add the new one to update the direction
            _registry.remove_component<Direction>(entity);
            _registry.add_component<Direction>(entity, Direction{directionX, directionY});
        } else {
            _registry.add_component<Direction>(entity, Direction{directionX, directionY});
        }
    } catch (const std::out_of_range& e) {
        std::cerr << "Entity not found direction update" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating the direction" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseObjectCollection(const std::string& message, int& index) {
    if (!checkMessageType("OBJECT_COLLECTION", message, index)) return false;

    unsigned int playerId;
    unsigned int objectId;

    try {
        std::memcpy(&playerId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&objectId, &message[index + 5], sizeof(unsigned int));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the object collection message" << std::endl;
        return false;
    }

    try {
        this->updateIndexFromBinaryData("object_collection", index);
        entity_t playerEntity = _registry.entity_from_index(playerId);
        entity_t objectEntity = _registry.entity_from_index(objectId);
        (void)playerEntity;
        (void)objectEntity;
        // Need to implement a mediator notification to the RenderEngine to create an animation for the object
        // collection
    } catch (const std::out_of_range& e) {
        std::cerr << "Entity not found" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating the object collection" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseProjectileFiring(const std::string& message, int& index) {
    if (!checkMessageType("PROJECTILE_FIRING", message, index)) return false;

    unsigned int shooterId;
    float posX;
    float posY;

    try {
        std::memcpy(&shooterId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the projectile firing message" << std::endl;
        return false;
    }

    this->updateIndexFromBinaryData("projectile_firing", index);
    // Need to implement a mediator notification to the RenderEngine to create an animation for the projectile
    // firing

    return true;
}

bool RType::ProtocolParsing::parseProjectileCollision(const std::string& message, int& index) {
    if (!checkMessageType("PROJECTILE_COLLISION", message, index)) return false;

    unsigned int projectileId;
    unsigned int entityId;

    try {
        std::memcpy(&projectileId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&entityId, &message[index + 5], sizeof(unsigned int));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the projectile collision message" << std::endl;
        return false;
    }

    try {
        entity_t projectileEntity = _registry.entity_from_index(projectileId);
        entity_t entity           = _registry.entity_from_index(entityId);
        (void)projectileEntity;
        (void)entity;
        this->updateIndexFromBinaryData("projectile_collision", index);
        // Need to implement the method to update the entity health and destroy the projectile
    } catch (const std::out_of_range& e) {
        std::cerr << "Entity not found projectile collision" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating the projectile collision" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseScoreUpdate(const std::string& message, int& index) {
    if (!checkMessageType("SCORE_UPDATE", message, index)) return false;

    unsigned int playerId;
    float score;

    try {
        std::memcpy(&playerId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&score, &message[index + 5], sizeof(float));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the score update message" << std::endl;
        return false;
    }

    this->updateIndexFromBinaryData("score_update", index);
    // Need to implement the method to update the player score

    return true;
}

bool RType::ProtocolParsing::parseShootSound(const std::string& message, int& index) {
    if (!checkMessageType("SHOOT_SOUND", message, index)) return false;

    _mediator->notify("ProtocolParsing", "ShootSound");
    this->updateIndexFromBinaryData("shoot_sound", index); // Ajoutez cette ligne pour mettre à jour l'index
    return true;
}

bool RType::ProtocolParsing::parseStateChange(const std::string& message, int& index) {
    if (!checkMessageType("STATE_CHANGE", message, index)) return false;

    unsigned int entityId;
    char state; // 1 byte state

    try {
        std::memcpy(&entityId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&state, &message[index + 5], sizeof(char));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the state change message" << std::endl;
        return false;
    }

    try {
        _mediator->notify("ProtocolParsing", "GameState " + std::to_string(int(state)));
        (void)entityId;
        this->updateIndexFromBinaryData("state_change", index);
        // Need to implement the method to update the entity state
    } catch (const std::out_of_range& e) {
        std::cerr << "Entity not found state change" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating the state" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseLevelUpdate(const std::string& message, int& index) {
    if (!checkMessageType("LEVEL_UPDATE", message, index)) return false;

    unsigned int level;

    try {
        std::memcpy(&level, &message[index + 1], sizeof(unsigned int));
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while parsing the level update message" << std::endl;
        return false;
    }

    try {
        _mediator->notify("ProtocolParsing", "GameLevel " + std::to_string(level));
        this->updateIndexFromBinaryData("level_update", index);
        loadAssetCfgEditorParsing(level);
        // Need to implement the method to update the entity state
    } catch (const std::out_of_range& e) {
        std::cerr << "Entity not found level update" << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while updating the level" << std::endl;
        return false;
    }
    return true;
}

bool RType::ProtocolParsing::parsePingClient(const std::string& message, int& index) {
    if (!checkMessageType("PING_CLIENT", message, index)) return false;

    std::string timeCode(&message[index + 1], message.size() - index - 1);

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm localtm;
#ifdef _WIN32
    gmtime_s(&localtm, &now_c);
#else
    gmtime_r(&now_c, &localtm);
#endif

    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%d/%H/%M/%S", &localtm);
    std::string local_time(buffer);

    std::chrono::duration<double> diff = std::chrono::system_clock::now() - now;

    _latency = diff.count() * 1000;

    this->updateIndexFromBinaryData("ping_client", index);
    return true;
}

bool RType::ProtocolParsing::parseData(const std::string& message) {
    if (message.empty()) return false;

    int index = 0;
    while (index < (int)message.size()) {
        if (this->parsePlayerCreation(message, index)) continue;
        if (this->parseProjectileCreation(message, index)) continue;
        if (this->parseEnemyCreation(message, index)) continue;
        if (this->parseMissileCreation(message, index)) continue;
        if (this->parseBigMissileCreation(message, index)) continue;
        if (this->parseShieldCreation(message, index)) continue;
        if (this->parseMachinegunCreation(message, index)) continue;
        if (this->parseRocketCreation(message, index)) continue;
        if (this->parseBeamCreation(message, index)) continue;
        if (this->parseCloneCreation(message, index)) continue;
        if (this->parseBossCreation(message, index)) continue;
        if (this->parseWallCreation(message, index)) continue;
        if (this->parseRewardCreation(message, index)) continue;
        if (this->parseEntityDeletion(message, index)) continue;
        if (this->parsePositionUpdate(message, index)) continue;
        if (this->parseHealthUpdate(message, index)) continue;
        if (this->parseDirectionUpdate(message, index)) continue;
        if (this->parseObjectCollection(message, index)) continue;
        if (this->parseProjectileFiring(message, index)) continue;
        if (this->parseProjectileCollision(message, index)) continue;
        if (this->parseScoreUpdate(message, index)) continue;
        if (this->parseStateChange(message, index)) continue;
        if (this->parseLevelUpdate(message, index)) continue;
        if (this->parseEntityCreation(message, index)) continue;
        if (this->parsePingClient(message, index)) continue;
        if (this->parseShootSound(message, index)) continue;
        index += 1;
    }
    return false;
}

void RType::ProtocolParsing::setMediator(std::shared_ptr<IMediator> mediator) {
    _mediator = mediator;
}

void RType::ProtocolParsing::setGameSelected(const std::string& gameSelected) {
    try {
        std::string gameConfigPath = std::string("config") + PATH_SEPARATOR + gameSelected + PATH_SEPARATOR + std::string("game_config.cfg");
        _gameConfig.readFile(gameConfigPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                  << std::endl;
    }
    loadAssetCfgEditorParsing(0);
}

void RType::ProtocolParsing::loadAssetCfgEditorParsing(size_t level)
{
    try {
        libconfig::Setting &levelConfig = _gameConfig.lookup("Menu.Game.level")[level];
        std::string cfgAssetEditorPath = levelConfig.lookup("sceneConfig");
        size_t startPos = 0;
        std::string from = "/";
        while((startPos = cfgAssetEditorPath.find(from, startPos)) != std::string::npos) {
            cfgAssetEditorPath.replace(startPos, from.length(), PATH_SEPARATOR);
            startPos += 2;
        }
        _cfgAssetEditor.readFile(cfgAssetEditorPath.c_str());
        _assetEditorParsing = std::make_unique<AssetEditorParsing>(_cfgAssetEditor);
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        throw std::runtime_error("I/O error while reading file.");
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                  << std::endl;
        throw std::runtime_error("Parse error");
    } catch (std::exception &e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
    }
}
