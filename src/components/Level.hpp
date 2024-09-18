/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Level
*/

#ifndef LEVEL_HPP_
    #define LEVEL_HPP_

    #include <cstddef>

    /**
     * @struct Level_s
     */
    typedef struct Level_s {
        /**
         * @brief Level component, add a level to an entity
         *
         */
        size_t level; //level of an entity (can't be negative)
    } Level;

#endif /* !LEVEL_HPP_ */
