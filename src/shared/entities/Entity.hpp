/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cstddef>

class Entity {
    public:
        explicit Entity(size_t value);
        operator size_t() const;

    private:
        size_t _value;
};

#endif /* !ENTITY_HPP_ */
