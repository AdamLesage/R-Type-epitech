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
    /**
     * @class IError interface of error class
     */
    class IError : public std::exception {
        public:
            /**
             * @brief Delete IError instance
             */
            virtual ~IError() noexcept = default;

            /**
             * @brief Show the error message while catching the error
             * @author Adam Lesage
             */
            virtual const char* what() const noexcept override = 0;

            /**
             * @brief Show the location of the error while catching the error
             * @author Adam Lesage
             */
            virtual const char* where() const noexcept = 0;

        protected:
    }; // class IError
} // namespace RType

#endif /* !IERROR_HPP_ */