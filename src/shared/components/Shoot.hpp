/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Shoot
*/

#ifndef SHOOT_HPP_
#define SHOOT_HPP_

#include <chrono>
/**
 * @struct Shoot_s
 */
typedef struct Shoot_s {
        /**
         * @brief Shoot component, add a shoot to an entity
         *
         */
        bool canShoot; // can the entity shoot
        std::chrono::steady_clock::time_point shootCooldown;
} Shoot;

#endif /* !SHOOT_HPP_ */
