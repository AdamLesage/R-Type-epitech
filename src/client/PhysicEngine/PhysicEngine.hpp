/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** PhysicEngine
*/

#ifndef PHYSICENGINE_HPP_
#define PHYSICENGINE_HPP_

#include "../AEngine.hpp"

namespace RType {
    class PhysicEngine : public AEngine {
        public:
            PhysicEngine();
            ~PhysicEngine();

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

#endif /* !PHYSICENGINE_HPP_ */
