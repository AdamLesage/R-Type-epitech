/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Patern
*/

#ifndef PATTERN_HPP_
#define PATTERN_HPP_

#include <chrono>

typedef struct Wave_pattern_s {
        /**
         * @brief PaternCompoent add a patern for an entity
         *
         */
        float amplitude; // oscillation
        float frequency; // Frequency of oscillation
        std::chrono::steady_clock::time_point creation;
} Wave_pattern;

#endif