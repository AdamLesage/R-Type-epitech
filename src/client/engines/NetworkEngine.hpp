/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkEngine
*/

#ifndef NETWORKENGINE_HPP_
#define NETWORKENGINE_HPP_

#include "AEngine.hpp"
#include "IMediator.hpp"

class NetworkEngine : public AEngine {
    public:
        NetworkEngine();
        ~NetworkEngine();

        /**
         * @brief Run current instance of the engine.
         */
        void run() override;
        void doSomething();
    protected:
    private:
};

#endif /* !NETWORKENGINE_HPP_ */
