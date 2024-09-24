/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderingEngine
*/

#ifndef RENDERINGENGINE_HPP_
#define RENDERINGENGINE_HPP_

#include "IMediator.hpp"

class RenderingEngine : public IMediator {
    public:
        RenderingEngine() {};
        ~RenderingEngine() {};

        void notify(std::string sender, std::string event) override {};
    protected:
    private:
};

#endif /* !RENDERINGENGINE_HPP_ */
