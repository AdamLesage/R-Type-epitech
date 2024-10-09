/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** EditConfigFile
*/

#ifndef EDITCONFIGFILE_HPP_
#define EDITCONFIGFILE_HPP_

#include <libconfig.h++>
#include <map>
#include <iostream>
#include <variant>

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
         * @brief Save and update the configuration file according to modificaitons in the queue.
         */
        void saveModifications();

        /**
         * @brief Add int value modification to the queue.
         * 
         * @param settingPath The path to setting to modify in config file
         * @param newValue The new value to replace the old one
         */
        void queueModification(const std::string &settingPath, int newValue);

        /**
         * @brief Add string value modification to the queue.
         * 
         * @param settingPath The path to setting to modify in config file
         * @param newValue The new value to replace the old one
         */
        void queueModification(const std::string &settingPath, const std::string &newValue);

        /**
         * @brief Return integer value of a setting.
         * 
         * @param settingPath The path to setting to return in config file
         */
        int getValueInt(const std::string &settingPath);

        /**
         * @brief Return string value of a setting.
         * 
         * @param settingPath The path to setting to return in config file
         */
        std::string getValueString(const std::string &settingPath);

    private:
        std::string configFilePath;
        libconfig::Config cfg;
        std::map<std::string, std::variant<int, std::string>> newValues;
};

#endif /* !EDITCONFIGFILE_HPP_ */
