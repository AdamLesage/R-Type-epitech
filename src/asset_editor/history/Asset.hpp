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
#include <any>
#include <typeindex>
#include "../../shared/components/Position.hpp"
#include "../../shared/components/Size.hpp"
#include "../../shared/components/Rotation.hpp"

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

            template<typename T>
            void addComponent(T &&component) {
                _components[std::type_index(typeid(std::decay_t<T>))] = std::forward<T>(component);
            }
            template<typename T>
            T& getComponent() {
                auto it = _components.find(std::type_index(typeid(std::decay_t<T>)));
                if (it == _components.end()) {
                    throw std::runtime_error("Component of this type not found");
                }
                return std::any_cast<T&>(it->second);
            }
        private:
            /**
             * @brief The position of the asset
             */
            Position _pos;

            /**
             * @brief the size of the asset
             */
            Size _size;

            /**
             * @brief the rotation of the asset
             */
            Rotation _rotation;


            /**
             * @brief The path to the asset
             */
            std::string _assetPath;
            sf::Texture *_spriteTexture;
            sf::RectangleShape _sprite;
            std::map<std::type_index, std::any> _components;
            std::string _entityCode;
    };
}; // namespace Edition

#endif /* !ASSET_HPP_ */
