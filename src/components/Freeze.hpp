/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Freeze
*/

#ifndef FREEZE_HPP_
    #define FREEZE_HPP_

    /**
     * @struct Freeze_s
     */
    typedef struct Freeze_s {
        /**
         * @brief Freeze component, add a freeze to an entity
         *
         */
        bool isFrozen;          //is the entity frozen
        bool isFreezeDamaging;  //is the entity damaging when frozen
    } Freeze;

#endif /* !FREEZE_HPP_ */
