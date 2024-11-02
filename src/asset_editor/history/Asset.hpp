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
#include "../../shared/components/Health.hpp"
#include "../../shared/components/PlayerFollowingPattern.hpp"
#include "../../shared/components/ShootStraightPattern.hpp"
#include "../../shared/components/ShootPlayerPattern.hpp"
#include "../../shared/components/StraightPattern.hpp"
#include "../../shared/components/Wave_Pattern.hpp"
#include "../../shared/components/Type.hpp"
#include "../../shared/components/Color.hpp"
#include "../../shared/components/Sprite.hpp"

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
            void draw(sf::RenderWindow& window);

            /**
             * @brief Get the entity code of the asset
             *
             * Entity code is the code given in PROTOCOL.md for each entity
             *
             * @return The entity code
             */
            std::string getEntityCode() const {
                return _entityCode;
            }

            /**
             * @brief Set the entity code of the asset
             *
             * @param code The entity code to set
             */
            void setEntityCode(std::string code) {
                _entityCode = code;
            }

            /**
             * @brief Get the global bounds of the asset.
             *
             * @return The bounding rectangle of the asset as an sf::FloatRect.
             */
            sf::FloatRect getGlobalBounds();

            /**
             * @brief Set the texture of the sprite.
             *
             * @param assetPath The path to the asset.
             */
            void setSpriteTexture(std::string assetPath);

            /**
             * @brief Adds a component to the asset.
             *
             * @tparam T The type of the component being added.
             * @param component The component to be added to the asset.
             */
            template <typename T> void addComponent(T&& component) {
                _components[std::type_index(typeid(std::decay_t<T>))] = std::forward<T>(component);
            }
            /**
             * @brief Retrieves a component of the specified type from the asset.
             *
             * @tparam T The type of the component to retrieve.
             * @return A reference to the component of the specified type.
             * @throws std::runtime_error If the component of the specified type is not found.
             */
            template <typename T> T& getComponent() {
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
            sf::Texture* _spriteTexture;
            sf::RectangleShape _sprite;
            std::map<std::type_index, std::any> _components;
            std::string _entityCode;
    };
}; // namespace Edition

#endif /* !ASSET_HPP_ */
