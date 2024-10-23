/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** LoadScene
*/


#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define LIB_EXTENSION ".dll"
    #define PATH_SEPARATOR "\\"
#else
    #include <dlfcn.h>
    #define LIB_EXTENSION ".so"
    #define PATH_SEPARATOR "/"
#endif

#include "LoadScene.hpp"

Edition::LoadScene::LoadScene(std::string &scenePath, std::vector<std::shared_ptr<Edition::Asset>> assets)
{
    _scenePath = scenePath;

    try {
        _cfg.readFile(_scenePath.c_str());
    } catch (const libconfig::ParseException &e) {
        std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine() << " - " << e.getError() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error from LoadScene constructor: " << e.what() << " for filename " << _scenePath << std::endl;
    }

    _assets = assets;
    _assets.clear(); // Remove all the entities to load scene
}

Edition::LoadScene::~LoadScene()
{
}

std::vector<std::shared_ptr<Edition::Asset>> Edition::LoadScene::load()
{
    std::string emptyAssetPath = std::string("assets") + PATH_SEPARATOR + "asset_editor" + PATH_SEPARATOR + "empty.png";

    try {
        libconfig::Setting &entities = _cfg.lookup("scene").lookup("entities");
        for (int i = 0; i < entities.getLength(); i++) {
            std::shared_ptr<Edition::Asset> asset = std::make_shared<Edition::Asset>(0, 0, emptyAssetPath, 0);
            libconfig::Setting &entity = entities[i];
            libconfig::Setting &components = entity.lookup("components");
            this->loadEntityCode(entity, asset);
            this->loadComponentSize(components, asset);
            this->loadComponentPosition(components, asset);
            this->loadComponentRotation(components, asset);
            this->loadComponentSprite(components, asset);
            _assets.push_back(asset);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error from LoadScene load: " << e.what() << " for filename " << _scenePath << std::endl;
    }

    return _assets;
}

void Edition::LoadScene::loadEntityCode(libconfig::Setting &entity, std::shared_ptr<Edition::Asset> asset)
{
    std::string code;
    try {
        // Check if the entity has a code
        if (!entity.exists("code")) {
            std::cerr << "Entity has no code" << std::endl;
            throw std::runtime_error("Entity has no code");
        }

        entity.lookupValue("code", code);
        asset->setEntityCode(code);
    } catch (const std::exception &e) {
        std::cerr << "Error from LoadScene loadEntityCode: " << e.what() << std::endl;
    }
}

void Edition::LoadScene::loadComponentSize(libconfig::Setting &components, std::shared_ptr<Edition::Asset> asset)
{
    try {
        libconfig::Setting &size = components.lookup("size");
        int x = size["x"];
        int y = size["y"];

        asset->addComponent<Size>(Size{(size_t)x, (size_t)y});
    } catch (const std::exception &e) {
        std::cerr << "Error from LoadScene loadComponentSize: " << e.what() << std::endl;
    }
}

void Edition::LoadScene::loadComponentPosition(libconfig::Setting &components, std::shared_ptr<Edition::Asset> asset)
{
    try {
        libconfig::Setting &position = components.lookup("position");
        int x = position["x"];
        int y = position["y"];
        asset->addComponent<Position>(Position{static_cast<float>(x), static_cast<float>(y)});
    } catch (const std::exception &e) {
        std::cerr << "Error from LoadScene loadComponentPosition: " << e.what() << std::endl;
    }
}
void Edition::LoadScene::loadComponentRotation(libconfig::Setting &components, std::shared_ptr<Edition::Asset> asset)
{
    try {
        libconfig::Setting &rotationSetting = components.lookup("rotation");
        int rotationAngle = rotationSetting;

        asset->addComponent<Rotation>(Rotation{static_cast<float>(rotationAngle)});
    } catch (const libconfig::SettingNotFoundException &e) {
        std::cerr << "Rotation setting not found: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error from LoadScene loadComponentRotation: " << e.what() << std::endl;
    }
}

void Edition::LoadScene::loadComponentSprite(libconfig::Setting &components, std::shared_ptr<Edition::Asset> asset)
{
    try {
        libconfig::Setting &spriteSettings = components.lookup("sprite");
        std::string spritePath = spriteSettings.lookup("path");
        int rectSizeX = spriteSettings.lookup("rectSize")[0];
        int rectSizeY = spriteSettings.lookup("rectSize")[1];
        int rectPosX = spriteSettings.lookup("rectPos")[0];
        int rectPosY = spriteSettings.lookup("rectPos")[1];

        asset->setSpriteTexture(spritePath);

        asset->addComponent<Sprite>(Sprite{spritePath, {rectSizeX, rectSizeY}, {rectPosX, rectPosY}});
    } catch (const std::exception &e) {
        std::cerr << "Error from LoadScene loadComponentSprite: " << e.what() << std::endl;
    }
}
