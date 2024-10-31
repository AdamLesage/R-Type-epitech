/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ParentId
*/

#ifndef PARENTID_HPP_
#define PARENTID_HPP_

#include <cstddef>

/**
 * @struct ParentId_s
 */
typedef struct ParentId_s {
        /**
         * @brief ParentId component, add a ParentId to an entity
         *
         */
        size_t ParentId; // ParentId of an entity (can't be negative)
} ParentId;

#endif /* !PARENTID_HPP_ */
