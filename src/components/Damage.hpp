/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Damage
*/

#ifndef DAMAGE_HPP_
#define DAMAGE_HPP_

#include <iostream>

namespace Component {
    class Damage {
        public:
            Damage();
            ~Damage();

        protected:
            std::size_t _damage;
        private:
    };
}

#endif /* !DAMAGE_HPP_ */
