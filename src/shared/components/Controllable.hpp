/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
    #define CONTROLLABLE_HPP_

    /**
     * @struct Controllable_s
     */
    typedef struct Controllable_s {
        /**
         * @brief Controllable component, add a controllable to an entity if it can be controlled
         *
         */
        bool isControllable; //is the entity controllable (ex: player = true, enemy = false)

        /**
         * @brief Values to check if the entity is moving up, down, left or right
         *
         */
        bool up;
        bool down;
        bool left;
        bool right;
    } Controllable;

#endif /* !CONTROLLABLE_HPP_ */
