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
#include "../../shared/utils/Logger.hpp"
#include "Scenes/Menu.hpp"
#include "Scenes/Game.hpp"
#include "Scenes/Settings.hpp"
#include "Scenes/Lobby.hpp"
#include "Scenes/EndMenu.hpp"
#include "../Camera.hpp"
#include "../../shared/registry/Registry.hpp"

#include <mutex>

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
            void setCamera(std::shared_ptr<Camera>& Camera);
            /**
             * @brief Set the mutex
             *
             * @param mutex the mutex to set
             */
            void setMutex(std::shared_ptr<std::mutex> mutex);

            void setRegistry(std::shared_ptr<Registry> registry) {
                this->_registry = registry; // _registry devrait être un pointeur partagé dans RenderingEngine
            }

            /**
             * @brief Set a new State
             * 
             *  @param newState the new state
             */
            void setStateGame(int newState);
            std::shared_ptr<Menu> getMenu() const { return _menu; }
            std::shared_ptr<Lobby> getLobby() const { return _lobby; }

            /**
             * @brief Set the game selected
             * 
             * @param gameSelected the game selected
             */
            void setGameSelected(const std::string& gameSelected) { _gameSelected = gameSelected; }

            /**
             * @brief Return current instance of currentGame, will be called by mediator to reset game
             * @brief _game is the class to display the game
             * @return current game instance
             * @author Adam Lesage
             */
            std::shared_ptr<Game> getCurrentGameDisplay() const { return _game; }
        private:
            std::shared_ptr<Menu> _menu;
            std::shared_ptr<sf::RenderWindow> window;
            std::shared_ptr<Game> _game;
            std::shared_ptr<Settings> _settings;
            std::shared_ptr<Lobby> _lobby;
            std::shared_ptr<EndMenu> _endMenu;
            std::shared_ptr<Camera> _camera;
            std::shared_ptr<std::mutex> _mutex;
            RType::Logger logger;
            int _stateGame = 1;
            std::string _gameSelected;
            std::shared_ptr<Registry> _registry;
    };
} // namespace RType

#endif /* !RENDERINGENGINE_HPP_ */
