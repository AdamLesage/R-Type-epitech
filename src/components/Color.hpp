/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <SFML/Graphics/Color.hpp>

namespace Component {
    class Color {
        public:
            Color();
            ~Color();

        protected:
            sf::Color _color;
        private:
    };
}

#endif /* !COLOR_HPP_ */
