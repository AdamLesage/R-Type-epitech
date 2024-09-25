/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AEngine
*/

#ifndef AENGINE_HPP_
#define AENGINE_HPP_

#include "IEngine.hpp"

namespace RType {
    class Mediator;
    class AEngine : public IEngine {
        public:
            AEngine(std::shared_ptr<IMediator> mediator = nullptr) : _mediator(mediator) {}
            ~AEngine() {}

            /**
             * @brief Set the mediator of the engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator) override { _mediator = mediator; }

            /**
             * @brief Run current instance of the engine.
             */
            void run() override {}
        protected:
            std::shared_ptr<IMediator> _mediator;
        private:
    };
}

#endif /* !AENGINE_HPP_ */
