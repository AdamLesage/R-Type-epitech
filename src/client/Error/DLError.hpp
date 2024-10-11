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
    class DLError : public AError {
        public:
            DLError(const std::string& message, const std::string& location) : AError(message, location) {
            }
            ~DLError() noexcept {
            }

        protected:
    };
} // namespace RType

#endif /* !DLERROR_HPP_ */