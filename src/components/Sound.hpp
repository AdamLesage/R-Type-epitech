/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <SFML/Audio.hpp>

namespace Component {
    class Sound {
        public:
            Sound();
            ~Sound();

        protected:
            sf::Sound _sound;
        private:
    };
}

#endif /* !SOUND_HPP_ */
