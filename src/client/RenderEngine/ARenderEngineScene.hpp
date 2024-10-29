/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ARenderEngineScene
*/

#ifndef ARENDERENGINESCENE_HPP_
#define ARENDERENGINESCENE_HPP_

#include "IRenderEngineScene.hpp"


namespace RType {
    class ARenderEngineScene : public IRenderEngineScene {
        public:
            ARenderEngineScene() = default;
            ~ARenderEngineScene();
            
            /**
             * @brief Run the scene
             *
             */
            virtual void runScene() override = 0;
            /**
             * @brief Set the mediator of the engine.
             *
             * @param mediator The mediator to set.
             */
            void setMediator(std::shared_ptr<IMediator> mediator) override;

            /**
             * @brief send a request of state change to the mediator
             * 
             * @param newState the state
             */
            void sendStateChange(int newState) override;
        protected:
            std::shared_ptr<IMediator> _mediator;
        private:
    };
};

#endif