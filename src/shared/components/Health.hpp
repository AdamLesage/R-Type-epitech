/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Health
*/

#ifndef HEALTH_HPP_
    #define HEALTH_HPP_

    #include <cstddef>

    /**
     * @struct Health_s
     */
    typedef struct Health_s {
        /**
         * @brief Health component, add a health to an entity
         *
         */
        size_t health;          //health of an entity
        size_t maxHealth;       //max health of an entity
        bool isRegenerating;    //is the entity regenerating health
        bool isDamageable;      //is the entity damageable
    } Health;

#endif /* !HEALTH_HPP_ */
