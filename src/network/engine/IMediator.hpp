/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** *
*/

#ifndef IMEDIATOR_HPP_
#define IMEDIATOR_HPP_

#include <string>

class IMediator {
    public:
        virtual ~IMediator() = default;
        virtual void notify(std::string sender, std::string event) = 0;

    protected:
    private:
};

#endif /* !IMEDIATOR_HPP_ */
