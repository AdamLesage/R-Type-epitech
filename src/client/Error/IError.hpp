/*
** EPITECH PROJECT, 2024
** IError.hpp
** File description:
** Error
*/

#ifndef IERROR_HPP_
#define IERROR_HPP_

#include <iostream>

namespace RType {
    class IError : public std::exception {
        public:
            virtual ~IError() noexcept = default;
            virtual const char* what() const noexcept override = 0;
            virtual const char* where() const noexcept = 0;

        protected:
    };
}

#endif /* !IERROR_HPP_ */