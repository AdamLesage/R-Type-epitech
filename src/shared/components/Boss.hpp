/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Boss
*/

#ifndef BOSS_HPP_
#define BOSS_HPP_

#include <chrono>

typedef struct BossPatern_s {
        /**
         * @brief BossPatern add a Boss patern to an entity
         *
         */
        float speed;
        bool up;
        bool down;
        float spawnCooldown;
        std::chrono::steady_clock::time_point lastSpawnTime;

} BossPatern;


#endif /* !BOSS_HPP_ */
