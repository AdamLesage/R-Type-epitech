/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** EditConfigFile
*/

#include "EditConfigFile.hpp"
#include <iostream>

EditConfigFile::EditConfigFile(const std::string &configFile) : configFilePath(configFile) {
    try {
        cfg.readFile(configFilePath.c_str());
        std::cout << "Config file loaded successfully" << std::endl;
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Error reading configuration file." << std::endl;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Error parsing file " << pex.getFile() << ":"
        << pex.getLine() << " - " << pex.getError() << std::endl;
    }
}

void EditConfigFile::readConfig() {
    try {
        int musicVolume = cfg.lookup("settings.volume.music");
        int sfxVolume = cfg.lookup("settings.volume.sfx");
        int windowWidth = cfg.lookup("settings.window.width");
        int windowHeight = cfg.lookup("settings.window.height");
        std::string keyUp = cfg.lookup("settings.controls.up");
        std::string keyDown = cfg.lookup("settings.controls.down");
        std::cout << "Music Volume: " << musicVolume << std::endl
                  << "SFX Volume: " << sfxVolume << std::endl
                  << "Screen Size: " << windowWidth << "x" << windowHeight << std::endl
                  << "Key Up: " << keyUp << std::endl
                  << "Key Down: " << keyDown << std::endl;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting missing in the configuration file." << std::endl;
    }
}

void EditConfigFile::modifyConfig(const std::string &settingPath, int newValue) {
    try {
        libconfig::Setting  &setting = cfg.lookup(settingPath);
        setting = newValue;

        cfg.writeFile(configFilePath.c_str());
        std::cout << "Configuration updated and saved." << std::endl;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting not found: " << settingPath << std::endl;
    } catch (const libconfig::SettingTypeException &tex) {
        std::cerr << "Invalid type for setting: " << settingPath << std::endl;
    }
}

void EditConfigFile::modifyConfig(const std::string &settingPath, const std::string &newValue) {
    try {
        libconfig::Setting  &setting = cfg.lookup(settingPath);
        setting = newValue;

        cfg.writeFile(configFilePath.c_str());
        std::cout << "Configuration updated and saved." << std::endl;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting not found: " << settingPath << std::endl;
    } catch (const libconfig::SettingTypeException &tex) {
        std::cerr << "Invalid type for setting: " << settingPath << std::endl;
    }
}
