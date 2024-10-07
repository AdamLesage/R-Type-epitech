/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderMediator
*/

#ifndef RENDERMEDIATOR_HPP_
#define RENDERMEDIATOR_HPP_

#include "../Mediator/IMediator.hpp"
#include "../AEngine.hpp"
#include <memory>

namespace RType {
    class RenderingEngine;
    class Menu;

    class RenderMediator {
        public:
            RenderMediator(std::shared_ptr<Menu> &menu, RType::AEngine *renderingEngine);
            ~RenderMediator();

            void notify(std::string sender, std::string event);
        protected:
        private:
            std::shared_ptr<Menu> _menu;
            RType::AEngine *_renderingEngine;
    };
}

#endif /* !RENDERMEDIATOR_HPP_ */
