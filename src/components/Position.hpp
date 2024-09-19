/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_

    #include <cstddef>

    /**
     * @struct Position_s
     */
    typedef struct Position_s {
        /**
         * @brief Position component, add a position to an entity (as size_t can't be negative)
         *
         */
        size_t x; //position on x axis
        size_t y; //position on y axis
    } Position;

#endif /* !POSITION_HPP_ */
