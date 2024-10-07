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
#include "Menu/Game.hpp"
#include "Menu/Settings.hpp"
#include "Menu/Lobby.hpp"

namespace RType {
    class RenderingEngine : public AEngine {
        public:
            RenderingEngine();
            ~RenderingEngine();

            /**
             * @brief Run current instance of the engine.
             */
            void run() override;
        protected:
        private:
            std::unique_ptr<Menu> _menu;
            std::shared_ptr<sf::RenderWindow> window;
            std::shared_ptr<Game> games;
            std::shared_ptr<Settings> settings;
            std::shared_ptr<Lobby> lobby;
    };
}

#endif /* !RENDERINGENGINE_HPP_ */
