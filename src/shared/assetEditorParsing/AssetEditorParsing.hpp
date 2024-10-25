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


typedef struct EntityData_s {
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
} EntityData;

class AssetEditorParsing {
    public:
        AssetEditorParsing(libconfig::Config &config);
        ~AssetEditorParsing();
        std::shared_ptr<EntityData> &getEntityData(uint8_t code);
    private:
        uint8_t parseCode(libconfig::Setting &entity);
        void parsePosition(EntityData &entityData, libconfig::Setting &components);
        void parseSize(EntityData &entityData, libconfig::Setting &components);
        void parseRotation(EntityData &entityData, libconfig::Setting &components);
        void parseHealth(EntityData &entityData, libconfig::Setting &components);
        void parseType(EntityData &entityData, libconfig::Setting &components);
        void parseTag(EntityData &entityData, libconfig::Setting &components);
        void parseSprite(EntityData &entityData, libconfig::Setting &components);
        void parseShootStraightPattern(EntityData &entityData, libconfig::Setting &components);
        void parsePlayerFollowingPattern(EntityData &entityData, libconfig::Setting &components);
        void parseShootPlayerPattern(EntityData &entityData, libconfig::Setting &components);
        void parseStraightLinePattern(EntityData &entityData, libconfig::Setting &components);
        void parseWavePattern(EntityData &entityData, libconfig::Setting &components);
        void parseAnnimation(EntityData &entityData, libconfig::Setting &components);
        std::vector<uint8_t> _code;
        std::map<uint8_t, std::shared_ptr<EntityData>> _entityData;

};

#endif /* !ASSETEDITORPARSING_HPP_ */
