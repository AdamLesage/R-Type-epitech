/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

    #include <SFML/Graphics.hpp>

    /**
     * @struct Sprite_s
     */
    typedef struct Sprite_s {
        /**
         * @brief Sprite component, add a sprite to an entity
         *
         */
        sf::Sprite sprite; //sprite of an entity
    } Sprite;

#endif /* !SPRITE_HPP_ */
