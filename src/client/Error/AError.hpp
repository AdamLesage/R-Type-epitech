/*
** EPITECH PROJECT, 2024
** AError.hpp
** File description:
** Error
*/

#ifndef AERROR_HPP_
#define AERROR_HPP_

#include "IError.hpp"
#include <iostream>

namespace RType {
    /**
     * @class AError abstract class for errors
     * @author Adam Lesage
     */
    class AError : public IError {
        public:
            /**
             * @brief construct a new error instance
             * @param message String to display while catching the error
             * @param location Current file or current function of the error thrown
             * @author Adam Lesage
             */
            AError(const std::string& message, const std::string& location) {
                _errorMessage  = message;
                _errorLocation = location;
            }

            /**
             * @brief Delete the current instance of the object
             * @author Adam Lesage
             */
            virtual ~AError() noexcept = default;

            /**
             * @brief Show the error message while catching the error
             * @author Adam Lesage
             */
            const char* what() const noexcept override {
                return (_errorMessage.c_str());
            }

            /**
             * @brief Show the location of the error while catching the error
             * @author Adam Lesage
             */
            const char* where() const noexcept override {
                return (_errorLocation.c_str());
            }

        protected:
            std::string _errorMessage;
            std::string _errorLocation;
    }; // class AError
} // namespace RType

#endif /* !AERROR_HPP_ */