/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Graphics.hpp>

namespace Component {
    class Sprite {
        public:
            Sprite();
            ~Sprite();

        protected:
            std::string _spritePath;
            sf::Sprite _sprite;
        private:
    };
}

#endif /* !SPRITE_HPP_ */
