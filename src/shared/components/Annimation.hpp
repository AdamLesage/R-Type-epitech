/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Annimation
*/

#ifndef ANNIMATION_HPP_
#define ANNIMATION_HPP_

#include <vector>
#include <array>
#include <chrono>
/**
 * @struct Animation_s
 */
typedef struct Annimation_s {
        /**
         * @brief Annimation component to manage entity animation
         *
         */
        float annimationSpeed;
        std::vector<std::array<int, 4>> annimation;
        size_t index;
        std::chrono::steady_clock::time_point lastExecution;
} Annimation;

#endif /* !ANNIMATION_HPP_ */
