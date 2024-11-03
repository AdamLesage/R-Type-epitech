/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetEditorParsing
*/

#ifndef ASSETEDITORPARSING_HPP_
#define ASSETEDITORPARSING_HPP_

#include <libconfig.h++>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <iostream>
#include "../components/Position.hpp"
#include "../components/Size.hpp"
#include "../components/Rotation.hpp"
#include "../components/ShootStraightPattern.hpp"
#include "../components/Health.hpp"
#include "../components/PlayerFollowingPattern.hpp"
#include "../components/Sprite.hpp"
#include "../components/Type.hpp"
#include "../components/Tag.hpp"
#include "../components/ShootPlayerPattern.hpp"
#include "../components/StraightPattern.hpp"
#include "../components/Wave_Pattern.hpp"
#include "../components/Annimation.hpp"
#include "../components/Boss.hpp"



#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

typedef struct EntityData_s {
    int number;
    std::shared_ptr<Position> pos;
    std::shared_ptr<Size> size;
    std::shared_ptr<Rotation> rotation;
    std::shared_ptr<Health> health;
    std::shared_ptr<Sprite> sprite;
    std::shared_ptr<Type> type;
    std::shared_ptr<Tag> tag;
    std::shared_ptr<ShootStraightPattern> shootStraightPattern;
    std::shared_ptr<PlayerFollowingPattern> playerFollowingPattern;
    std::shared_ptr<ShootPlayerPattern> shootPlayerPattern;
    std::shared_ptr<StraightLinePattern> straightLinePattern;
    std::shared_ptr<Wave_pattern> WavePattern;
    std::shared_ptr<Annimation> annimation;
    std::shared_ptr<BossPatern> bossPatern;
} EntityData;

class AssetEditorParsing {
    public:
        /**
         * @brief Constructor that initializes AssetEditorParsing with a reference to a libconfig::Config object.
         * @param config Reference to a libconfig configuration object.
         */
        AssetEditorParsing(libconfig::Config &config);

        /**
         * Destructor for AssetEditorParsing.
         */
        ~AssetEditorParsing();

        /**
         * @brief Retrieves entity data associated with the given code.
         * @param code The unique code identifying the entity.
         * @return Shared pointer to the EntityData associated with the code.
         */
        std::shared_ptr<EntityData> &getEntityData(uint8_t code);

        /**
         * @brief Retrieves entities data.
         * @return map of entity
         */
        std::map<uint8_t, std::shared_ptr<EntityData>> &getEntities();

    private:
        /**
         * @brief Parses the code for a given entity setting.
         * @param entity The entity setting to parse the code from.
         * @return Parsed code as an unsigned 8-bit integer.
         */
        uint8_t parseCode(libconfig::Setting &entity);

        /**
         * @brief Parses the number for a given entity setting.
         * @param entity The entity setting to parse the number from.
         * @return Parsed number as an int.
         */
        int parseNumber(libconfig::Setting &entity);

        /**
         * @brief Parses the position component of an entity and populates the EntityData structure.
         * @param entityData Reference to EntityData where parsed position is stored.
         * @param components Setting containing position component data.
         */
        void parsePosition(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses the size component of an entity and populates the EntityData structure.
         * @param entityData Reference to EntityData where parsed size is stored.
         * @param components Setting containing size component data.
         */
        void parseSize(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses the rotation component of an entity and populates the EntityData structure.
         * @param entityData Reference to EntityData where parsed rotation is stored.
         * @param components Setting containing rotation component data.
         */
        void parseRotation(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses the health component of an entity and populates the EntityData structure.
         * @param entityData Reference to EntityData where parsed health is stored.
         * @param components Setting containing health component data.
         */
        void parseHealth(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses the type component of an entity and populates the EntityData structure.
         * @param entityData Reference to EntityData where parsed type is stored.
         * @param components Setting containing type component data.
         */
        void parseType(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses the tag component of an entity and populates the EntityData structure.
         * @param entityData Reference to EntityData where parsed tag is stored.
         * @param components Setting containing tag component data.
         */
        void parseTag(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses the sprite component of an entity and populates the EntityData structure.
         * @param entityData Reference to EntityData where parsed sprite data is stored.
         * @param components Setting containing sprite component data.
         */
        void parseSprite(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses a shoot-straight pattern component of an entity.
         * @param entityData Reference to EntityData where parsed pattern data is stored.
         * @param components Setting containing shoot-straight pattern data.
         */
        void parseShootStraightPattern(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses a player-following pattern component of an entity.
         * @param entityData Reference to EntityData where parsed pattern data is stored.
         * @param components Setting containing player-following pattern data.
         */
        void parsePlayerFollowingPattern(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses a shoot-player pattern component of an entity.
         * @param entityData Reference to EntityData where parsed pattern data is stored.
         * @param components Setting containing shoot-player pattern data.
         */
        void parseShootPlayerPattern(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses a straight-line pattern component of an entity.
         * @param entityData Reference to EntityData where parsed pattern data is stored.
         * @param components Setting containing straight-line pattern data.
         */
        void parseStraightLinePattern(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses a wave pattern component of an entity.
         * @param entityData Reference to EntityData where parsed pattern data is stored.
         * @param components Setting containing wave pattern data.
         */
        void parseWavePattern(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses a boss pattern component of an entity.
         * @param entityData Reference to EntityData where parsed pattern data is stored.
         * @param components Setting containing boss pattern data.
         */
        void parseBossPattern(EntityData &entityData, libconfig::Setting &components);

        /**
         * @brief Parses animation data for an entity.
         * @param entityData Reference to EntityData where parsed animation data is stored.
         * @param components Setting containing animation data.
         */
        void parseAnnimation(EntityData &entityData, libconfig::Setting &components);

        std::vector<uint8_t> _code;
        std::map<uint8_t, std::shared_ptr<EntityData>> _entityData;
};

#endif /* !ASSETEDITORPARSING_HPP_ */
