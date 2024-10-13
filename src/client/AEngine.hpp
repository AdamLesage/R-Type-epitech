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
    class AEngine : public IEngine {
        public:
            AEngine(std::shared_ptr<IMediator> mediator);
            AEngine() = default;
            ~AEngine();

            /**
             * @brief Set the mediator of the engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator) override;

            /**
             * @brief Run current instance of the engine.
             */
            void run() override;

            std::shared_ptr<IMediator>
                _mediator; // Public attribute to be able to access it from the derived class.
        protected:
        private:
    };
} // namespace RType

#endif /* !AENGINE_HPP_ */
