/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Tag
*/

#ifndef TAG_HPP_
#define TAG_HPP_

#include <string>

/**
 * @struct Tag_s
 */
typedef struct Tag_s {
        /**
         * @brief Tag component, add a tag to an entity
         *
         */
        std::string tag; // tag of the entity (ex: player, enemy, bullet)
} Tag;

#endif /* !TAG_HPP_ */
