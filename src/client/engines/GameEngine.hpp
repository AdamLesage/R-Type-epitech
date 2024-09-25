/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "AEngine.hpp"
#include "../../shared/entities/Entity.hpp"
#include "../../shared/registry/Registry.hpp"
#include "../../shared/systems/Systems.hpp"
#include "../../shared/sparse_array/SparseArray.hpp"

class GameEngine : public AEngine {
    public:
        GameEngine();
        ~GameEngine();

        /**
         * @brief Run current instance of the engine.
         */
        void run() override;
    protected:
    private:
        Registry _registry;
        Systems _systems;
        sf::RenderWindow _window;
};

#endif /* !GAMEENGINE_HPP_ */
