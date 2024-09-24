/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** EditConfigFile
*/

#include "EditConfigFile.hpp"

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

void EditConfigFile::saveModifications() {
    for (const auto &mod : newValues) {
        try {
            libconfig::Setting &setting = cfg.lookup(mod.first);

            std::visit([&setting](auto&& value) {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<T, int>) {
                    setting = value;
                } else if constexpr (std::is_same_v<T, std::string>) {
                    setting = value.c_str();
                }
            }, mod.second);
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found: " << mod.first << std::endl;
        } catch (const libconfig::SettingTypeException &tex) {
            std::cerr << "Invalid type for setting: " << mod.first << std::endl;
        }
    }
    try {
        cfg.writeFile(configFilePath.c_str());
        std::cout << "Modifications saved in the configuration file." << std::endl;
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Error writting in the configuration file." << std::endl;
    }
    newValues.clear();
}

void EditConfigFile::queueModification(const std::string &settingPath, int newValue) {
    newValues[settingPath] = newValue;
}

void EditConfigFile::queueModification(const std::string &settingPath, const std::string &newValue) {
    newValues[settingPath] = newValue;
}
