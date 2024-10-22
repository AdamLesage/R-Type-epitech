/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Asset
*/

#ifndef ASSET_HPP_
#define ASSET_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

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
            Asset(int x, int y, std::string assetPath, size_t entityCode);

            /**
             * @brief Destroy the Asset object
             */
            ~Asset();

            /**
             * @brief Move the asset
             * 
             * @param dx The x offset
             * @param dy The y offset
             */
            void move(int dx, int dy);

            /**
             * @brief Draw the asset
             * 
             * @param window The window of the Asset Editor
             */
            void draw(sf::RenderWindow &window);

            /**
             * @brief Get the entity code of the asset
             * 
             * Entity code is the code given in PROTOCOL.md for each entity
             * 
             * @return The entity code
             */
            std::string getEntityCode() const { return _entityCode; }

            sf::FloatRect getGlobalBounds();
        private:
            /**
             * @brief The x position of the asset
             */
            int _x;

            /**
             * @brief The y position of the asset
             */
            int _y;

            /**
             * @brief The path to the asset
             */
            std::string _assetPath;
            sf::Texture _spriteTexture;
            sf::Sprite _sprite;
            std::string _entityCode;
    };
}; // namespace Edition

#endif /* !ASSET_HPP_ */
