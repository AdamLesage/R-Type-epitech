/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderingEngine
*/

#ifndef RENDERINGENGINE_HPP_
#define RENDERINGENGINE_HPP_

#include "../AEngine.hpp"
#include "../Mediator/IMediator.hpp"
#include "Menu/Menu.hpp"

namespace RType {
    class RenderingEngine : public AEngine {
        public:
            RenderingEngine();
            ~RenderingEngine();

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
            std::unique_ptr<Menu> _menu;
    };
}

#endif /* !RENDERINGENGINE_HPP_ */
