/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** SaveScene
*/

#ifndef SAVESCENE_HPP_
#define SAVESCENE_HPP_

#include <libconfig.h++>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <vector>

#include "../history/Asset.hpp"

namespace Edition {

    /**
     * @brief Save Scene of the Asset Editor into a cfg file
     */
    class SaveScene {
        public:
            /**
             * @brief Construct a new Save Scene object
             */
            SaveScene(std::string scenePath, std::vector<std::shared_ptr<Asset>> assets);

            /**
             * @brief Destroy the Save Scene object
             */
            ~SaveScene();

            /**
             * @brief Save the scene into a cfg file
             */
            void save();

        protected:
        private:
            /**
             * @brief Write the entity code into the file such as "code: "0x01",
             */
            void saveEntityCode(std::ofstream &outFile, std::shared_ptr<Asset> asset);

            /**
             * @brief Write the component position into the file such as "position: {x: 100, y: 100}",
             * 
             * @param outFile The file to write into
             * @param asset The asset to save
             */
            void saveComponentPosition(std::ofstream &outFile, std::shared_ptr<Asset> asset);

            /**
             * @brief Write the component size into the file such as "size: {x: 100, y: 100}",
             * 
             * @param outFile The file to write into
             * @param asset The asset to save
             */
            void saveComponentSize(std::ofstream &outFile, std::shared_ptr<Asset> asset);

            /**
             * @brief Write the component rotation into the file such as "rotation: 0",
             * 
             * @param outFile The file to write into
             * @param asset The asset to save
             */
            void saveComponentRotation(std::ofstream &outFile, std::shared_ptr<Asset> asset);

            std::string _scenePath;
            std::vector<std::shared_ptr<Asset>> _assets;
            libconfig::Config _cfg;
    };
}

#endif /* !SAVESCENE_HPP_ */
