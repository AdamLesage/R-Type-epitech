/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Size
*/

#ifndef SIZE_HPP_
    #define SIZE_HPP_

    #include <cstddef>

    /**
     * @struct Size_s
     */
    typedef struct Size_s {
        /**
         * @brief Size component, add a size to an entity
         *
         */
        size_t x; //size X of an entity
        size_t y; //size Y of an entity
    } Size;

#endif /* !SIZE_HPP_ */
