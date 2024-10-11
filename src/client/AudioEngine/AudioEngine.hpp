/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AudioEngine
*/

#ifndef AUDIOENGINE_HPP_
#define AUDIOENGINE_HPP_

#include "../AEngine.hpp"

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

        protected:
        private:
    };
} // namespace RType

#endif /* !AUDIOENGINE_HPP_ */
