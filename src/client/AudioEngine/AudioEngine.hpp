/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AudioEngine
*/

#ifndef AUDIOENGINE_HPP_
#define AUDIOENGINE_HPP_

#include <SFML/Audio.hpp>
#include "../AEngine.hpp"
#include "../Mediator/IMediator.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif /* PATH_SEPARATOR */

namespace RType {
    class AudioEngine : public AEngine {
        public:
            AudioEngine();
            ~AudioEngine();

            /**
             * @brief Run current instance of the engine.
             */
            void run() override;

            /**
             * @brief Set the mediator of the engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator) override;

            /**
             * @brief Play the shoot sound.
             */
            void ShootSound();

            /**
             * @brief Play the launch music.
             */
            void launch_music_play();

            /**
             * @brief Stop the launch music.
             */
            void launch_music_stop();

            /**
             * @brief Play the select sound.
             */
            void selectSoundPlay();

            /**
             * @brief Adjust the volume of the background music.
             *
             * @param increase If true, increase the volume; otherwise, decrease it.
             */
            void adjustVolume(bool increase);

            /**
             * @brief Get the volume of the background music.
             */
            void BackgroundMusicGetVolume();

            /**
             * @brief Play the background music.
             */
            void backgroundMusicPlay();

            /**
             * @brief Stop the background music.
             */
            void backgroundMusicStop();

            /**
             * @brief Get the volume of the second background music.
             */
            void BackgroundMusicGetVolume2();

            /**
             * @brief Play the second background music.
             */
            void backgroundMusicPlay2();

            /**
             * @brief Stop the second background music.
             */
            void backgroundMusicStop2();

            /**
             * @brief Adjust the volume of the second background music.
             *
             * @param increase If true, increase the volume; otherwise, decrease it.
             */
            void adjustVolume2(bool increase);

        protected:
            sf::SoundBuffer game_launch_sound; // The buffer of the game launch sound
            sf::Sound game_launch_music;       // The sound of the game launch
            sf::SoundBuffer shoot_sound;       // The buffer of the shoot sound
            sf::Sound shoot_music;             // The sound of the shoot
            sf::SoundBuffer shoot_sound2;      // The buffer of the shoot sound 2
            sf::Sound shoot_music2;            // The sound of the shoot 2
            sf::Sound backgroundMusic;         // The background music of the Lobby
            sf::SoundBuffer backgroundBuffer;  // The buffer of the background music
            sf::SoundBuffer selectBuffer;      // The buffer of the select sound
            sf::Sound selectSound;             // The sound played when selecting an option
            sf::SoundBuffer backgroundBuffer2; // The buffer of the background music
            sf::Sound backgroundMusic2;        // The background music
        private:
    };
} // namespace RType

#endif /* !AUDIOENGINE_HPP_ */
