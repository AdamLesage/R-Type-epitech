/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <array>
/**
 * @struct Sprite_s
 */
typedef struct Sprite_s {
        /**
         * @brief Sprite component, add a sprite to an entity
         *
         */
        std::string spritePath; // sprite of an entity
        std::array<int, 2> rectSize;
        std::array<int, 2> rectPos;
} Sprite;

#endif /* !SPRITE_HPP_ */
