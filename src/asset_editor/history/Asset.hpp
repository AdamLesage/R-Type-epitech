/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Asset
*/

#ifndef ASSET_HPP_
#define ASSET_HPP_

#include <iostream>

namespace Edition {
    /**
     * @brief Asset of the Asset Editor
     */
    class Asset {
        public:
            /**
             * @brief Construct a new Asset object
             * 
             * @param x The x position of the asset
             * @param y The y position of the asset
             * @param assetPath The path to the asset
             */
            Asset(int x, int y, std::string assetPath);
            ~Asset();
            void move(int dx, int dy);

        private:
            int _x;
            int _y;
            std::string _assetPath;
    }; // class Asset
} // namespace Edition

#endif /* !ASSET_HPP_ */
