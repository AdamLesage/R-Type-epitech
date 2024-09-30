/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ProtocolParsing
*/

#ifndef PROTOCOLPARSING_HPP_
#define PROTOCOLPARSING_HPP_

#include <iostream>
#include <libconfig.h++>

namespace RType {
    class ProtocolParsing {
        public:
            ProtocolParsing(std::string protocolPath);
            ~ProtocolParsing();

        protected:
        private:
            std::string _protocolPath;
            libconfig::Config _cfg;
    };
}

#endif /* !PROTOCOLPARSING_HPP_ */
