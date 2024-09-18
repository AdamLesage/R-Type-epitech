/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Sound
*/

#ifndef SOUND_HPP_
    #define SOUND_HPP_

    #include <SFML/Audio.hpp>
    #include <cstddef>

    /**
     * @struct Sound_s
     */
    typedef struct Sound_s {
        /**
         * @brief Sound component, add a sound to an entity
         *
         */
        sf::Sound sound; //sound of an entity
        size_t volume;   //volume of an entity
    } Sound;

#endif /* !SOUND_HPP_ */
