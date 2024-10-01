/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AudioEngine
*/

#ifndef AUDIOENGINE_HPP_
#define AUDIOENGINE_HPP_

#include "../AEngine.hpp"
#include "../Mediator/IMediator.hpp"

namespace RType {
    class AudioEngine : public AEngine {
        public:
            AudioEngine();
            ~AudioEngine();

            /**
             * @brief Run current instance of the engine.
             */
            void run() override;
        protected:
        private:
    };
}

#endif /* !AUDIOENGINE_HPP_ */
