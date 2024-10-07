/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderMediator
*/

#ifndef RENDERMEDIATOR_HPP_
#define RENDERMEDIATOR_HPP_

#include "../Mediator/IMediator.hpp"
#include "../IEngine.hpp"
#include <memory>

namespace RType {
    class RenderingEngine;
    class Menu;

    class RenderMediator : public IMediator {
        public:
            RenderMediator(std::shared_ptr<Menu> &menu, std::shared_ptr<RenderingEngine> renderingEngine);
            ~RenderMediator();

            void notify(std::string sender, std::string event) override;
        protected:
        private:
            std::shared_ptr<Menu> _menu;
            std::shared_ptr<RenderingEngine> _renderingEngine;
    };
}

#endif /* !RENDERMEDIATOR_HPP_ */
