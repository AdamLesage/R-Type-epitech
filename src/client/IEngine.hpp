/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** IEngine
*/

#ifndef IENGINE_HPP_
#define IENGINE_HPP_

#include <memory>
#include <iostream>

namespace RType {
    class IMediator;
    class IEngine {
        public:
            virtual ~IEngine() = default;

            /**
             * @brief Set the mediator of the engine.
             *
             * @param mediator The mediator to set.
             */
            virtual void setMediator(std::shared_ptr<IMediator> mediator) = 0;

            /**
             * @brief Run current instance of the engine.
             */
            virtual void run() = 0;
        protected:
        private:
    };
}

#endif /* !IENGINE_HPP_ */
