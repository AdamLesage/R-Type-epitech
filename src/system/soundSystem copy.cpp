/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** controlSystem
*/

#include "../Registery.hpp"
#include "../components/Sound.hpp"

void sound_system(Registery &r)
{
    auto const &sounds = r.get_components<sound>();
    for (size_t i = 0; i < sounds.size(); ++i) {
        auto const &sound = sounds[i];
        if (sound) {
            if (sound.value()->isPlaying) {
                sound.value()->sound.play();
            }
        }
    }
    sound.value()->sound.setVolume(sound.value()->volume);
}