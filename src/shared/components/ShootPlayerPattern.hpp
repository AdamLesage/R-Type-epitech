/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ShootPlayerPattern
*/

#ifndef SHOOTPLAYERPATTERN_HPP_
#define SHOOTPLAYERPATTERN_HPP_

#include <chrono>

typedef struct ShootPlayerPattern_s {
        /**
         * @brief ShootPlayerPattern add a ShootPlayer patern to an entity
         *
         */
        float projectileSpeed;
        float shootCooldown;
        std::chrono::steady_clock::time_point lastShotTime;
} ShootPlayerPattern;

#endif /* !SHOOTPLAYERPATTERN_HPP_ */
