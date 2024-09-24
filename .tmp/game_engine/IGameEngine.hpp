/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** IGameEngine
*/

#ifndef IGAMEENGINE_HPP_
#define IGAMEENGINE_HPP_

class IGameEngine {
    public:
        virtual ~IGameEngine() = default;

        virtual void startGame() = 0;

    protected:
    private:
};

#endif /* !IGAMEENGINE_HPP_ */
