/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ProtocolParsing
*/

#include "ProtocolParsing.hpp"

RType::ProtocolParsing::ProtocolParsing(std::string protocolPath, Registry &registry)
    : _registry(registry)
{
    try {
        _protocolPath = protocolPath;
        _cfg.readFile(_protocolPath.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    } catch (const libconfig::ParseException &pex) {
        std::cerr   << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                    << " - " << pex.getError() << std::endl;
    }

    _messageTypeMap = {
        {"PLAYER_CREATION", {0x01, "player_creation"}},
        {"PROJECTILE_CREATION", {0x02, "projectile_creation"}},
        {"ENEMY_CREATION", {0x03, "enemy_creation"}},
        {"BONUS_CREATION", {0x21, "bonus_creation"}},
        {"WALL_CREATION", {0x25, "wall_creation"}},
        {"REWARD_CREATION", {0x26, "reward_creation"}},
        {"ENTITY_DELETION", {0x29, "entity_deletion"}},
        {"POSITION_UPDATE", {0x30, "position_update"}},
        {"HEALTH_UPDATE", {0x31, "health_update"}},
        {"DIRECTION_UPDATE", {0x32, "direction_update"}},
        {"OBJECT_COLLECTION", {0x33, "object_collection"}},
        {"PROJECTILE_FIRING", {0x34, "projectile_firing"}},
        {"PROJECTILE_COLLISION", {0x35, "projectile_collision"}},
        {"SCORE_UPDATE", {0x36, "score_update"}},
        {"STATE_CHANGE", {0x37, "state_change"}}
    };
}

RType::ProtocolParsing::~ProtocolParsing()
{
}

bool RType::ProtocolParsing::checkMessageType(const std::string &messageType, const std::string &message, int &index)
{
    // Check if message is for the current parsing function such as current type (0xXX) is correct
    if (static_cast<uint8_t>(message[index]) != _messageTypeMap[messageType].first)
        return false;

    // Check if the message type is a byte
    if (sizeof(message[index]) != sizeof(uint8_t))
        return false;

    // Compare message size with the expected size in the protocol config file
    if (!_cfg.exists("protocol")) {
        return false;
    }
    auto &protocol = _cfg.lookup("protocol");
    if (!protocol.exists(_messageTypeMap[messageType].second)) {
        return false;
    }
    auto &element = protocol.lookup(_messageTypeMap[messageType].second);
    if (!element.exists("total_size")) {
        return false;
    }
    try {
        int totalSize = element.lookup("total_size");
        if (static_cast<int>(message.length()) - index < totalSize) {
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

bool RType::ProtocolParsing::parsePlayerCreation(const std::string &message, int &index)
{
    if (!checkMessageType("PLAYER_CREATION", message, index))
        return false;

    unsigned int playerId;
    float posX;
    float posY;

    try {
        std::cout << index << std::endl;
        std::memcpy(&playerId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the player creation message" << std::endl;
        return false;
    }

    try {
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
        _registry.add_component<Size>(entity, Size{100, 100});
        _registry.add_component<Direction>(entity, Direction{1, 0});
        _registry.add_component<Sprite>(entity, Sprite{"../asset/player/player_1.png"});
        index += 12;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while creating the player" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseProjectileCreation(const std::string &message, int &index)
{
    if (!checkMessageType("PROJECTILE_CREATION", message, index))
        return false;

    unsigned int projectileId;
    float posX;
    float posY;
    unsigned int parentId;

    try {
        std::memcpy(&projectileId, &message[1], sizeof(unsigned int));
        std::memcpy(&posX, &message[5], sizeof(float));
        std::memcpy(&posY, &message[9], sizeof(float));
        std::memcpy(&parentId, &message[13], sizeof(unsigned int));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the projectile creation message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"projectile"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Damage>(entity, Damage{10});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Size>(entity, Size{50, 10});
        _registry.add_component<Direction>(entity, Direction{0, 0});
        _registry.add_component<Sprite>(entity, Sprite{"../asset/bullet/missile_1.png"});
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while creating the projectile" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseEnemyCreation(const std::string &message, int &index)
{
    if (!checkMessageType("ENEMY_CREATION", message, index))
        return false;

    unsigned int enemyId;
    float posX;
    float posY;

    try {
        std::memcpy(&enemyId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the enemy creation message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"enemy"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Health>(entity, Health{100, 100, true, true});
        _registry.add_component<Damage>(entity, Damage{10});
        _registry.add_component<Level>(entity, Level{1});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Size>(entity, Size{100, 100});
        _registry.add_component<Direction>(entity, Direction{-1, 0});
        _registry.add_component<Sprite>(entity, Sprite{"../asset/ennemy/enemy_2.png"});
        index += 12;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while creating the enemy" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseBonusCreation(const std::string &message, int &index)
{
    if (!checkMessageType("BONUS_CREATION", message, index))
        return false;

    unsigned int bonusId;
    float posX;
    float posY;

    try {
        std::memcpy(&bonusId, &message[1], sizeof(unsigned int));
        std::memcpy(&posX, &message[5], sizeof(float));
        std::memcpy(&posY, &message[9], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the bonus creation message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"bonus"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while creating the bonus" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseWallCreation(const std::string &message, int &index)
{
    if (!checkMessageType("WALL_CREATION", message, index))
        return false;

    unsigned int wallId;
    float posX;
    float posY;
    float width;
    float height;

    try {
        std::memcpy(&wallId, &message[1], sizeof(unsigned int));
        std::memcpy(&posX, &message[5], sizeof(float));
        std::memcpy(&posY, &message[9], sizeof(float));
        std::memcpy(&width, &message[13], sizeof(float));
        std::memcpy(&height, &message[17], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the wall creation message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"wall"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
        _registry.add_component<Health>(entity, Health{100, 100, false, false}); // We can destroy the wall with a projectile
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while creating the wall" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseRewardCreation(const std::string &message, int &index)
{
    if (!checkMessageType("REWARD_CREATION", message, index))
        return false;

    unsigned int rewardId;
    float posX;
    float posY;
    float width;
    float height;

    try {
        std::memcpy(&rewardId, &message[1], sizeof(unsigned int));
        std::memcpy(&posX, &message[5], sizeof(float));
        std::memcpy(&posY, &message[9], sizeof(float));
        std::memcpy(&width, &message[13], sizeof(float));
        std::memcpy(&height, &message[17], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the reward creation message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.spawn_entity();
        _registry.add_component<Position>(entity, Position{posX, posY});
        _registry.add_component<Tag>(entity, Tag{"reward"});
        _registry.add_component<Scale>(entity, Scale{1});
        _registry.add_component<Rotation>(entity, Rotation{0});
        _registry.add_component<Velocity>(entity, Velocity{0, 0});
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while creating the reward" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseEntityDeletion(const std::string &message, int &index)
{
    if (!checkMessageType("ENTITY_DELETION", message, index))
        return false;

    unsigned int entityId;

    try {
        std::memcpy(&entityId, &message[1], sizeof(unsigned int));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the entity deletion message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.entity_from_index(entityId);
        _registry.kill_entity(entity);
    } catch (const std::out_of_range &e) {
        std::cerr << "Entity not found" << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while deleting the entity" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parsePositionUpdate(const std::string &message, int &index)
{
    if (!checkMessageType("POSITION_UPDATE", message, index))
        return false;

    unsigned int entityId;
    float posX;
    float posY;

    try {
        std::memcpy(&entityId, &message[index + 1], sizeof(unsigned int));
        std::memcpy(&posX, &message[index + 5], sizeof(float));
        std::memcpy(&posY, &message[index + 9], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the position update message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.entity_from_index(entityId);

        // Check if the entity has a position component
        index += 12;
        auto optionalPositionComponent = _registry.get_components<Position>()[entity];
        if (optionalPositionComponent.has_value() == false) { // If the entity doesn't have a position component, add it
            _registry.add_component<Position>(entity, Position{posX, posY});
            return true;
        }

        // Remove the old position component and add the new one to update the position
        _registry.remove_component<Position>(entity);
        _registry.add_component<Position>(entity, Position{posX, posY});
    } catch (const std::out_of_range &e) {
        std::cerr << "Entity not found" << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while updating the position" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseHealthUpdate(const std::string &message, int &index)
{
    if (!checkMessageType("HEALTH_UPDATE", message, index))
        return false;

    unsigned int entityId;
    unsigned int health;

    try {
        std::memcpy(&entityId, &message[1], sizeof(unsigned int));
        std::memcpy(&health, &message[5], sizeof(unsigned int));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the health update message" << std::endl;
        return false;
    }

    try {
        entity_t entity = _registry.entity_from_index(entityId);
        auto optionalHealthComponent = _registry.get_components<Health>()[entity];

        // Check if the entity has a health component
        if (optionalHealthComponent.has_value()) {
            Health &healthComponent = optionalHealthComponent.value();
            // Remove the old health component and add the new one to update the health
            _registry.remove_component<Health>(entity);
            _registry.add_component<Health>(entity, Health{health, healthComponent.maxHealth, healthComponent.isRegenerating, healthComponent.isDamageable});
        } else {
            _registry.add_component<Health>(entity, Health{health, 100, true, true});
        }
    } catch (const std::out_of_range &e) {
        std::cerr << "Entity not found" << std::endl;
        return false;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while updating the health" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseDirectionUpdate(const std::string &message, int &index)
{
    if (!checkMessageType("DIRECTION_UPDATE", message, index))
        return false;

    unsigned int entityId;
    float directionX;
    float directionY;

    try {
        std::memcpy(&entityId, &message[1], sizeof(unsigned int));
        std::memcpy(&directionX, &message[5], sizeof(float));
        std::memcpy(&directionY, &message[9], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the direction update message" << std::endl;
        return false;
    }

    return true;
}

bool RType::ProtocolParsing::parseObjectCollection(const std::string &message, int &index)
{
    if (!checkMessageType("OBJECT_COLLECTION", message, index))
        return false;

    unsigned int playerId;
    unsigned int objectId;

    try {
        std::memcpy(&playerId, &message[1], sizeof(unsigned int));
        std::memcpy(&objectId, &message[5], sizeof(unsigned int));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the object collection message" << std::endl;
        return false;
    }

    // Need to implement a way to know if the object is collected by the player

    return true;
}

bool RType::ProtocolParsing::parseProjectileFiring(const std::string &message, int &index)
{
    if (!checkMessageType("PROJECTILE_FIRING", message, index))
        return false;

    unsigned int shooterId;
    float posX;
    float posY;

    try {
        std::memcpy(&shooterId, &message[1], sizeof(unsigned int));
        std::memcpy(&posX, &message[5], sizeof(float));
        std::memcpy(&posY, &message[9], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the projectile firing message" << std::endl;
        return false;
    }

    // Need to implement a mediator notification to the RenderEngine to create an animation for the projectile firing

    return true;
}

bool RType::ProtocolParsing::parseProjectileCollision(const std::string &message, int &index)
{
    if (!checkMessageType("PROJECTILE_COLLISION", message, index))
        return false;

    unsigned int projectileId;
    unsigned int entityId;

    try {
        std::memcpy(&projectileId, &message[1], sizeof(unsigned int));
        std::memcpy(&entityId, &message[5], sizeof(unsigned int));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the projectile collision message" << std::endl;
        return false;
    }

    // Need to implement the method to remove health point and destroy the projectile

    return true;
}

bool RType::ProtocolParsing::parseScoreUpdate(const std::string &message, int &index)
{
    if (!checkMessageType("SCORE_UPDATE", message, index))
        return false;

    unsigned int playerId;
    float score;

    try {
        std::memcpy(&playerId, &message[1], sizeof(unsigned int));
        std::memcpy(&score, &message[5], sizeof(float));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the score update message" << std::endl;
        return false;
    }

    // Need to implement the method to update the player score

    return true;
}

bool RType::ProtocolParsing::parseStateChange(const std::string &message, int &index)
{
    if (!checkMessageType("STATE_CHANGE", message, index))
        return false;

    unsigned int entityId;
    char state; // 1 byte state

    try {
        std::memcpy(&entityId, &message[1], sizeof(unsigned int));
        std::memcpy(&state, &message[5], sizeof(char));
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while parsing the state change message" << std::endl;
        return false;
    }

    // Need to create a component state to update the entity state

    return true;
}

bool RType::ProtocolParsing::parseData(const std::string &message)
{
    if (message.empty())
        return false;

    int index = 0;
    while (index < (int)message.size()) {
        this->parsePlayerCreation(message, index);
        this->parseProjectileCreation(message, index);
        this->parseEnemyCreation(message, index);
        this->parseBonusCreation(message, index);
        this->parseWallCreation(message, index);
        this->parseRewardCreation(message, index);
        this->parseEntityDeletion(message, index);
        this->parsePositionUpdate(message, index);
        this->parseHealthUpdate(message, index);
        this->parseDirectionUpdate(message, index);
        this->parseObjectCollection(message, index);
        this->parseProjectileFiring(message, index);
        this->parseProjectileCollision(message, index);
        this->parseScoreUpdate(message, index);
        this->parseStateChange(message, index);
        index += 1;
    }
    // auto &positions = this->_registry.get_components<Position>();
    // auto &tags = this->_registry.get_components<Tag>();
    // for (size_t i = 0; i < positions.size(); ++i) {
    //     auto &pos = positions[i];
    //     auto &tag = tags[i];

    //     if (pos && tag) {
    //         std::cout << "entity: " << i << " pos X: " << pos->x << " pos Y: " << pos->y << std::endl;
    //     }
    // }

    return false;
}
