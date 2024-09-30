/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** PhysicEngine
*/

#ifndef PHYSICENGINE_HPP_
#define PHYSICENGINE_HPP_

#include "../AEngine.hpp"
#include "../Mediator/IMediator.hpp"

namespace RType {
    class PhysicEngine : public AEngine {
        public:
            PhysicEngine();
            ~PhysicEngine();

            /**
             * @brief Run current instance of the engine.
             */
            void run() override;
        protected:
        private:
    };
}

#endif /* !PHYSICENGINE_HPP_ */
