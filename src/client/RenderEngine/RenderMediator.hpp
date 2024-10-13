/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderMediator
*/

#ifndef RENDERMEDIATOR_HPP_
#define RENDERMEDIATOR_HPP_

#include "../Mediator/IMediator.hpp"
#include "Menu/Menu.hpp"
#include <memory>

namespace RType {
    class Menu;
    class RenderingEngine;

    class RenderMediator : public IMediator {
        public:
            RenderMediator(std::unique_ptr<Menu>& menu, std::shared_ptr<RenderingEngine> renderingEngine);
            ~RenderMediator();

            void notify(std::string sender, const std::string& event) override;

        protected:
        private:
            std::unique_ptr<Menu> _menu;
            std::shared_ptr<RenderingEngine> _renderingEngine;
    };
} // namespace RType

#endif /* !RENDERMEDIATOR_HPP_ */
