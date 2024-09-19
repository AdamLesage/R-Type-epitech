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
            bool _isPlaying;
            size_t _volume;
        private:
    };
}

#endif /* !SOUND_HPP_ */
