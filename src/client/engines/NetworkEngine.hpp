/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkEngine
*/

#ifndef NETWORKENGINE_HPP_
#define NETWORKENGINE_HPP_

#include "IMediator.hpp"

namespace NetworkLib {
    class NetworkEngine : public IMediator {
        public:
            NetworkEngine() {}
            ~NetworkEngine() {}

            void notify(std::string sender, std::string event) override {};
        protected:
        private:
    };
}

#endif /* !NETWORKENGINE_HPP_ */
