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

bool RType::ProtocolParsing::checkMessageType(const std::string &messageType, const char *message)
{
    // Check if message is for the current parsing function such as current type (0xXX) is correct
    if (static_cast<uint8_t>(message[0]) != _messageTypeMap[messageType].first)
        return false;

    // Check if the message type is a byte
    if (sizeof(message[0]) != sizeof(uint8_t))
        return false;

    // Compare message size with the expected size in the protocol config file
    if (strlen(message) != std::stoi(_cfg.lookup(_messageTypeMap[messageType].second)["total_size"]))
        return false;
    return true;
}

bool RType::ProtocolParsing::parsePlayerCreation(const char *message)
{
    if (!checkMessageType("PLAYER_CREATION", message))
        return false;

    unsigned int playerId;
    float posX;
    float posY;

    std::memcpy(&playerId, &message[1], sizeof(unsigned int));
    std::memcpy(&posX, &message[5], sizeof(float));
    std::memcpy(&posY, &message[9], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseProjectileCreation(const char *message)
{
    if (!checkMessageType("PROJECTILE_CREATION", message))
        return false;

    unsigned int projectileId;
    float posX;
    float posY;
    unsigned int parentId;

    std::memcpy(&projectileId, &message[1], sizeof(unsigned int));
    std::memcpy(&posX, &message[5], sizeof(float));
    std::memcpy(&posY, &message[9], sizeof(float));
    std::memcpy(&parentId, &message[13], sizeof(unsigned int));

    return true;
}

bool RType::ProtocolParsing::parseEnemyCreation(const char *message)
{
    if (!checkMessageType("ENEMY_CREATION", message))
        return false;

    unsigned int enemyId;
    float posX;
    float posY;

    std::memcpy(&enemyId, &message[1], sizeof(unsigned int));
    std::memcpy(&posX, &message[5], sizeof(float));
    std::memcpy(&posY, &message[9], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseBonusCreation(const char *message)
{
    if (!checkMessageType("BONUS_CREATION", message))
        return false;

    unsigned int bonusId;
    float posX;
    float posY;

    std::memcpy(&bonusId, &message[1], sizeof(unsigned int));
    std::memcpy(&posX, &message[5], sizeof(float));
    std::memcpy(&posY, &message[9], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseWallCreation(const char *message)
{
    if (!checkMessageType("WALL_CREATION", message))
        return false;

    unsigned int wallId;
    float posX;
    float posY;
    float width;
    float height;

    std::memcpy(&wallId, &message[1], sizeof(unsigned int));
    std::memcpy(&posX, &message[5], sizeof(float));
    std::memcpy(&posY, &message[9], sizeof(float));
    std::memcpy(&width, &message[13], sizeof(float));
    std::memcpy(&height, &message[17], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseRewardCreation(const char *message)
{
    if (!checkMessageType("REWARD_CREATION", message))
        return false;

    unsigned int rewardId;
    float posX;
    float posY;
    float width;
    float height;

    std::memcpy(&rewardId, &message[1], sizeof(unsigned int));
    std::memcpy(&posX, &message[5], sizeof(float));
    std::memcpy(&posY, &message[9], sizeof(float));
    std::memcpy(&width, &message[13], sizeof(float));
    std::memcpy(&height, &message[17], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseEntityDeletion(const char *message)
{
    if (!checkMessageType("ENTITY_DELETION", message))
        return false;

    unsigned int entityId;

    std::memcpy(&entityId, &message[1], sizeof(unsigned int));

    return true;
}

bool RType::ProtocolParsing::parsePositionUpdate(const char *message)
{
    if (!checkMessageType("POSITION_UPDATE", message))
        return false;

    unsigned int entityId;
    float posX;
    float posY;

    std::memcpy(&entityId, &message[1], sizeof(unsigned int));
    std::memcpy(&posX, &message[5], sizeof(float));
    std::memcpy(&posY, &message[9], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseHealthUpdate(const char *message)
{
    if (!checkMessageType("HEALTH_UPDATE", message))
        return false;

    unsigned int entityId;
    unsigned int health;

    std::memcpy(&entityId, &message[1], sizeof(unsigned int));
    std::memcpy(&health, &message[5], sizeof(unsigned int));

    return true;
}

bool RType::ProtocolParsing::parseDirectionUpdate(const char *message)
{
    if (!checkMessageType("DIRECTION_UPDATE", message))
        return false;

    unsigned int entityId;
    float directionX;
    float directionY;

    std::memcpy(&entityId, &message[1], sizeof(unsigned int));
    std::memcpy(&directionX, &message[5], sizeof(float));
    std::memcpy(&directionY, &message[9], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseObjectCollection(const char *message)
{
    if (!checkMessageType("OBJECT_COLLECTION", message))
        return false;

    unsigned int playerId;
    unsigned int objectId;

    std::memcpy(&playerId, &message[1], sizeof(unsigned int));
    std::memcpy(&objectId, &message[5], sizeof(unsigned int));

    return true;
}

bool RType::ProtocolParsing::parseProjectileFiring(const char *message)
{
    if (!checkMessageType("PROJECTILE_FIRING", message))
        return false;

    unsigned int shooterId;
    float posX;
    float posY;

    std::memcpy(&shooterId, &message[1], sizeof(unsigned int));
    std::memcpy(&posX, &message[5], sizeof(float));
    std::memcpy(&posY, &message[9], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseProjectileCollision(const char *message)
{
    if (!checkMessageType("PROJECTILE_COLLISION", message))
        return false;

    unsigned int projectileId;
    unsigned int entityId;

    std::memcpy(&projectileId, &message[1], sizeof(unsigned int));
    std::memcpy(&entityId, &message[5], sizeof(unsigned int));

    return true;
}

bool RType::ProtocolParsing::parseScoreUpdate(const char *message)
{
    if (!checkMessageType("SCORE_UPDATE", message))
        return false;

    unsigned int playerId;
    float score;

    std::memcpy(&playerId, &message[1], sizeof(unsigned int));
    std::memcpy(&score, &message[5], sizeof(float));

    return true;
}

bool RType::ProtocolParsing::parseStateChange(const char *message)
{
    if (!checkMessageType("STATE_CHANGE", message))
        return false;

    unsigned int entityId;
    char state; // 1 byte state

    std::memcpy(&entityId, &message[1], sizeof(unsigned int));
    std::memcpy(&state, &message[5], sizeof(char));

    return true;
}

bool RType::ProtocolParsing::parseData(const char *message)
{
    if (message == nullptr)
        return false;

    // Array of results
    bool results[] = {
        this->parsePlayerCreation(message),
        this->parseProjectileCreation(message),
        this->parseEnemyCreation(message),
        this->parseBonusCreation(message),
        this->parseWallCreation(message),
        this->parseRewardCreation(message),
        this->parseEntityDeletion(message),
        this->parsePositionUpdate(message),
        this->parseHealthUpdate(message),
        this->parseDirectionUpdate(message),
        this->parseObjectCollection(message),
        this->parseProjectileFiring(message),
        this->parseProjectileCollision(message),
        this->parseScoreUpdate(message),
        this->parseStateChange(message)
    };

    // Check if any of the results is true
    for (bool result : results) {
        if (result) {
            return true;
        }
    }

    return false;
}
