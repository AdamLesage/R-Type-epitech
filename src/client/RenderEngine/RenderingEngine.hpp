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
#include "../Camera.hpp"

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
            /**
             * @brief Set the camera of the game
             * 
             * @param Camera the Camera to set
             */
            void setCamera(std::shared_ptr<Camera> &Camera);
        protected:
        private:
            std::shared_ptr<Menu> _menu;
            std::shared_ptr<sf::RenderWindow> window;
            std::shared_ptr<Game> games;
            std::shared_ptr<Settings> settings;
            std::shared_ptr<Lobby> lobby;
            std::shared_ptr<Camera> _camera;
    };
}

#endif /* !RENDERINGENGINE_HPP_ */
