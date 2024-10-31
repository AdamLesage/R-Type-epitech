/*
** EPITECH PROJECT, 2024
** DLError.hpp
** File description:
** DLError
*/

#ifndef DLERROR_HPP_
#define DLERROR_HPP_

#include "AError.hpp"

namespace RType {
    /**
     * @class DLError class
     * @author Adam Lesage
     */
    class DLError : public AError {
        public:
            /**
             * @brief Construct a new DLError instance
             * @author Adam Lesage
             */
            DLError(const std::string& message, const std::string& location) : AError(message, location) {
            }

            /**
             * @brief Delete the current DLError instance
             * @author Adam Lesage
             */
            ~DLError() noexcept {
            }

        protected:
    }; // class DLError
} // namespace RType

#endif /* !DLERROR_HPP_ */