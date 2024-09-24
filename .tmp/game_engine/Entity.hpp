/*
** EPITECH PROJECT, 2024
** B-CPP-500-NAN-5-1-bsrtype-romain.chevallier
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <cstddef>
#include <unordered_map>
#include <typeindex>
#include <any>

class Entity {
    public:
        Entity(size_t uuid);
        ~Entity();
        operator std::size_t() const {
            return this->_uuid;
        }
    protected:
    private:
        std::size_t _uuid;
};

#endif /* !ENTITY_HPP_ */
