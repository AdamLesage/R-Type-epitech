/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
    #define DRAWABLE_HPP_

    #include <SFML/Graphics.hpp>

    /**
     * @struct Drawable (For debugging/test purposes)
     */
    typedef struct Drawable_s {
        /**
         * @brief Drawable component, add a drawable to an entity
         *
         */
        sf::RectangleShape shape;  //rectangle shape to draw
    } Drawable;

#endif /* !DRAWABLE_HPP_ */
