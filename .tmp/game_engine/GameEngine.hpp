/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "IGameEngine.hpp"
#include "Registery.hpp"

class GameEngine : public IGameEngine {
    public:
        GameEngine();
        ~GameEngine();

    protected:
        Registery _registery;
    private:
};

#endif /* !GAMEENGINE_HPP_ */
