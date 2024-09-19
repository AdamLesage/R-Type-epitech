/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Shoot
*/

#ifndef SHOOT_HPP_
#define SHOOT_HPP_

namespace Component {
    class Shoot {
        public:
            Shoot();
            ~Shoot();

        protected:
            bool _canShoot;
            float _shootingSpeed;

        private:
    };
}

#endif /* !SHOOT_HPP_ */
