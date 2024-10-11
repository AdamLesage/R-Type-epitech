/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ShootStraightPattern
*/

#ifndef SHOOTSTRAIGHTPATTERN_HPP_
#define SHOOTSTRAIGHTPATTERN_HPP_

#include <chrono>

typedef struct ShootStraightPattern_s {
        /**
         * @brief ShootStraightPattern add a ShootStraight pattern to an entity
         *
         */
        float projectileSpeed;
        float shootCooldown;
        std::chrono::steady_clock::time_point lastShotTime;
} ShootStraightPattern;

#endif /* !SHOOTSTRAIGHTPATTERN_HPP_ */
