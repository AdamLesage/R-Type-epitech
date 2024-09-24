/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** EditConfigFile
*/

#ifndef EDITCONFIGFILE_HPP_
#define EDITCONFIGFILE_HPP_

#include <string>
#include <libconfig.h++>

class EditConfigFile {
    public:
        /**
         * @brief Constructor for EditConfigFile.
         * 
         * @param configFile The path to config file
         */
        EditConfigFile(const std::string &configFile);

        /**
         * @brief Default desctructor for EditConfigFile. 
         */
        ~EditConfigFile() = default;

        /**
         * @brief Read the configuration file.
         */
        void readConfig();

        /**
         * @brief Modify config file's int value.
         * 
         * @param settingPath The path to setting to modify in config file
         * @param newValue The new value to replace the old one
         */
        void modifyConfig(const std::string &settingPath, int newValue);

        /**
         * @brief Modify config file's string value.
         * 
         * @param settingPath The path to setting to modify in config file
         * @param newValue The new value to replace the old one
         */
        void modifyConfig(const std::string &settingPath, const std::string &newValue);

    private:
        std::string configFilePath;
        libconfig::Config cfg;
};

#endif /* !EDITCONFIGFILE_HPP_ */
