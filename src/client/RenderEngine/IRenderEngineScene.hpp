/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** IRenderEngineScene
*/

#ifndef IRENDERENGINESCENE_HPP_
#define IRENDERENGINESCENE_HPP_

#include <memory>
#include "../Mediator/IMediator.hpp"

namespace RType {
    class IRenderEngineScene {
        public:
            virtual ~IRenderEngineScene() = default;

            /**
             * @brief Run the scene
             *
             */
            virtual void runScene(float& latency) = 0;
            /**
             * @brief Set the mediator of the engine.
             *
             * @param mediator The mediator to set.
             */
            virtual void setMediator(std::shared_ptr<IMediator> mediator) = 0;

            /**
             * @brief send a request of state change to the mediator
             *
             * @param newState the state
             */
            virtual void sendStateChange(int newState) = 0;

        protected:
        private:
    };
}; // namespace RType

#endif /* !IRENDERENGINESCENE_HPP_ */
