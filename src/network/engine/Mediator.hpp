/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Mediator
*/

#ifndef MEDIATOR_HPP_
#define MEDIATOR_HPP_

#include <string>
#include <memory>
#include "IMediator.hpp"
#include "GameEngine.hpp"
#include "NetworkEngine.hpp"
#include "RenderingEngine.hpp"

class Mediator : public IMediator {
    public:
        Mediator();
        ~Mediator();

        void notify(std::string sender, std::string event) override;
    protected:
        void notifyGameEngine(std::string sender, std::string event);
        void notifyNetworkEngine(std::string sender, std::string event);
        void notifyRenderingEngine(std::string sender, std::string event);
    private:
        std::shared_ptr<GameEngine> _gameEngine;
        std::shared_ptr<NetworkLib::NetworkEngine> _networkEngine;
        std::shared_ptr<RenderingEngine> _renderingEngine;
};

#endif /* !MEDIATOR_HPP_ */
