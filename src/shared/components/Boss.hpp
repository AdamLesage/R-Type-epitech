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
        float RegenCooldown; // regen cooldown of the boss
        std::chrono::steady_clock::time_point lastRegenTime; // last regen time of the boss
} BossPatern;


#endif /* !BOSS_HPP_ */
