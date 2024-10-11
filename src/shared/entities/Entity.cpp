/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Entity
*/

#include "Entity.hpp"

Entity::Entity(size_t value) : _value(value) {
}

Entity::operator size_t() const {
    return _value;
}