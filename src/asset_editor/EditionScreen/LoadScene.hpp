/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** LoadScene
*/

#ifndef LOADSCENE_HPP_
#define LOADSCENE_HPP_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <libconfig.h++>
#include <string>

#include "../history/Asset.hpp"

namespace Edition {
    /**
     * @brief Load the scene
     */
    class LoadScene {
        public:
            /**
             * @brief Construct a new Load Scene object
             * 
             * @param scenePath The path of the scene to load
             * @param assets The assets to load
             */
            LoadScene(std::string &scenePath, std::vector<std::shared_ptr<Edition::Asset>> assets);

            /**
             * @brief Destroy the Load Scene object
             */
            ~LoadScene();

            /**
             * @brief Load the scene with the given name
             * 
             * @return std::vector<std::shared_ptr<Edition::Asset>> The assets loaded
             */
            std::vector<std::shared_ptr<Edition::Asset>> load();

        protected:
        private:
            /**
             * @brief Load the entity code
             * 
             * @param entity The entity given from config file
             * @param asset The asset to load and attach the entity code
             */
            void loadEntityCode(libconfig::Setting &entity, std::shared_ptr<Edition::Asset> asset);

            /**
             * @brief Load the entity code
             * 
             * @param components The components given from config file
             * @param asset The asset to load and attach the component
             */
            void loadComponentSize(libconfig::Setting &components, std::shared_ptr<Edition::Asset> asset);

            /**
             * @brief Load the component position
             * 
             * @param components The components given from config file
             * @param asset The asset to load and attach the component
             */
            void loadComponentPosition(libconfig::Setting &components, std::shared_ptr<Edition::Asset> asset);

            /**
             * @brief Load the component rotation
             * 
             * @param components The components given from config file
             * @param asset The asset to load and attach the component
             */
            void loadComponentRotation(libconfig::Setting &components, std::shared_ptr<Edition::Asset> asset);

            std::string _scenePath;
            libconfig::Config _cfg;
            std::vector<std::shared_ptr<Edition::Asset>> _assets;
    };
}

#endif /* !LOADSCENE_HPP_ */
