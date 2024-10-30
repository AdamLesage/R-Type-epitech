/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetEditorParsing
*/

#include "AssetEditorParsing.hpp"

AssetEditorParsing::AssetEditorParsing(libconfig::Config &config)
{
    libconfig::Setting &entities = config.lookup("scene").lookup("entities");
    for (int i = 0; i < entities.getLength(); i++) {
        libconfig::Setting &entity = entities[i];
        libconfig::Setting &components = entity.lookup("components");
        EntityData entityData;
        uint8_t entityCode = parseCode(entity);
        entityData.number = parseNumber(entity);
        if (entityCode == 0) {
            continue;
        }
        parsePosition(entityData, components);
        parseRotation(entityData, components);
        parseSize(entityData, components);
        parseSprite(entityData, components);
        parseHealth(entityData, components);
        parseType(entityData, components);
        parseTag(entityData, components);
        parseShootStraightPattern(entityData, components);
        parsePlayerFollowingPattern(entityData, components);
        parseShootPlayerPattern(entityData, components);
        parseStraightLinePattern(entityData, components);
        parseWavePattern(entityData, components);
        parseAnnimation(entityData, components);
        this->_entityData[entityCode] = std::make_shared<EntityData>(entityData);
    }
}

AssetEditorParsing::~AssetEditorParsing()
{
}


std::shared_ptr<EntityData> &AssetEditorParsing::getEntityData(uint8_t code)
{
    return this->_entityData[code];
}

std::map<uint8_t, std::shared_ptr<EntityData>> &AssetEditorParsing::getEntities() {
    return this->_entityData;
}

uint8_t AssetEditorParsing::parseCode(libconfig::Setting &entity)
{
    int code;
    try {
        // Check if the entity has a code
        if (!entity.exists("code")) {
            std::cerr << "Entity has no code" << std::endl;
            throw std::runtime_error("Entity has no code");
        }

        entity.lookupValue("code", code);
        return code;
    } catch (const std::exception&) {
        return 0;
    }
    return 0;
}

int AssetEditorParsing::parseNumber(libconfig::Setting &entity)
{
    int number;
    try {
        // Check if the entity has a code
        if (!entity.exists("number")) {
            std::cerr << "Entity has no code" << std::endl;
            throw std::runtime_error("Entity has no code");
        }

        entity.lookupValue("number", number);
        return number;
    } catch (const std::exception&) {
        return 0;
    }
    return 0;
}

void AssetEditorParsing::parsePosition(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &position = components.lookup("position");
        int x = position["x"];
        int y = position["y"];
        entityData.pos = std::make_shared<Position>(Position{static_cast<float>(x), static_cast<float>(y)});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseSize(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &size = components.lookup("size");
        int x = size["x"];
        int y = size["y"];
        entityData.size = std::make_shared<Size>(Size{static_cast<size_t>(x), static_cast<size_t>(y)});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseRotation(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &rotationSetting = components.lookup("rotation");
        int rotationAngle = rotationSetting;

        entityData.rotation = std::make_shared<Rotation>(Rotation{static_cast<float>(rotationAngle)});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseSprite(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &spriteSettings = components.lookup("sprite");
        std::string spritePath = spriteSettings.lookup("path");
        int rectSizeX = spriteSettings.lookup("rectSize")[0];
        int rectSizeY = spriteSettings.lookup("rectSize")[1];
        int rectPosX = spriteSettings.lookup("rectPos")[0];
        int rectPosY = spriteSettings.lookup("rectPos")[1];
        size_t startPos = 0;
        std::string from = "/";
        while((startPos = spritePath.find(from, startPos)) != std::string::npos) {
            spritePath.replace(startPos, from.length(), PATH_SEPARATOR);
            startPos += 2;
        }
        entityData.sprite = std::make_shared<Sprite>(Sprite{spritePath, {rectSizeX, rectSizeY}, {rectPosX, rectPosY}});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseHealth(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &healthSetting = components.lookup("health");
        int health = healthSetting.lookup("health");
        int isRegenerating = healthSetting.lookup("isRegenerating");
        int isDamageable = healthSetting.lookup("isDamageable");
        entityData.health = std::make_shared<Health>(Health{static_cast<unsigned long>(health), static_cast<unsigned long>(health), (bool)isRegenerating, (bool)isDamageable});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseType(EntityData &entityData, libconfig::Setting &components)
{
    std::map<std::string, EntityType> entityMap = {
        {"PLAYER", PLAYER},
        {"ENEMY", ENEMY},
        {"PLAYER_PROJECTILE", PLAYER_PROJECTILE},
        {"ENEMY_PROJECTILE", ENEMY_PROJECTILE},
        {"BACKGROUND", BACKGROUND},
        {"OBSTACLE", OBSTACLE},
        {"POWERUP", POWERUP}
    };
    try {
        libconfig::Setting &typeSetting = components.lookup("type");
        std::string typeString = typeSetting;

        entityData.type = std::make_shared<Type>(Type{entityMap[typeString]});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseTag(EntityData &entityData, libconfig::Setting &components)
{
    (void)entityData;
    (void)components;
}

void AssetEditorParsing::parseShootStraightPattern(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &shootStraightPatternSetting = components.lookup("shootStraightPattern");
        float shootCooldown = shootStraightPatternSetting["shootCooldown"];
        float projectileSpeed = shootStraightPatternSetting["projectileSpeed"];
        entityData.shootStraightPattern = std::make_shared<ShootStraightPattern>(ShootStraightPattern{projectileSpeed, shootCooldown, std::chrono::steady_clock::now()});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseShootPlayerPattern(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &shootPlayerPatternSetting = components.lookup("shootPlayerPattern");
        float shootCooldown = shootPlayerPatternSetting["shootCooldown"];
        float projectileSpeed = shootPlayerPatternSetting["projectileSpeed"];
        entityData.shootPlayerPattern = std::make_shared<ShootPlayerPattern>(ShootPlayerPattern{projectileSpeed, shootCooldown, std::chrono::steady_clock::now()});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parsePlayerFollowingPattern(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &playerFollowingPatternSetting = components.lookup("playerFollowingPattern");
        float speed = playerFollowingPatternSetting["speed"];
        entityData.playerFollowingPattern = std::make_shared<PlayerFollowingPattern>(PlayerFollowingPattern{speed});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseStraightLinePattern(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &StraightLinePatternSetting = components.lookup("straightLinePattern");
        float speed = StraightLinePatternSetting["speed"];
        entityData.straightLinePattern = std::make_shared<StraightLinePattern>(StraightLinePattern{speed});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseWavePattern(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &WavePatternSetting = components.lookup("wave_pattern");
        float amplitude = WavePatternSetting["amplitude"];
        float frequency = WavePatternSetting["frequency"];
        entityData.WavePattern = std::make_shared<Wave_pattern>(Wave_pattern{amplitude, frequency});
    } catch (const std::exception&) {
        return;
    }
}

void AssetEditorParsing::parseAnnimation(EntityData &entityData, libconfig::Setting &components)
{
    try {
        libconfig::Setting &annimationSettings = components.lookup("annimation");
        libconfig::Setting &steps = annimationSettings["steps"];
        float annimationSpeed = annimationSettings["annimationSpeed"];
        Annimation annimation;
        for (int i = 0; steps.getLength() != i; i++) {
            libconfig::Setting &step = steps[i];
            annimation.annimation.push_back({step[0], step[1],step[2],step[3]});
        }
        annimation.index = 0;
        annimation.lastExecution = std::chrono::steady_clock::now();
        annimation.annimationSpeed = annimationSpeed;
        entityData.annimation = std::make_shared<Annimation>(annimation);
    } catch (const std::exception&) {
        return;
    }
}
