/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

#include <iostream>

namespace Component {
    class Health {
        public:
            Health();
            ~Health();

        protected:
            std::size_t _health;
            bool _isAlive;
            bool _isDamageable;
        private:
    };
}

#endif /* !HEALTH_HPP_ */
