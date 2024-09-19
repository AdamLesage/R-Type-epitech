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
    } Controllable;

#endif /* !CONTROLLABLE_HPP_ */
