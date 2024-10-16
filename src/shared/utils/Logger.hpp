/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include <cstdio>
#include <cstdarg>

namespace RType {
    class Logger {
        public:
            enum LogType { RTYPEINFO, RTYPEWARN, RTYPEERROR, RTYPEDEBUG };

            /**
             * @brief Construct a new Logger object
             */
            Logger() = default;

            /**
             * @brief Destroy the Logger object
             */
            ~Logger() = default;

            /**
             * @brief Log a message with a type
             * @param type LogType
             * @param message Formatted message
             */
            void log(LogType type, const char* message, ...);
    };
} // namespace RType
#endif /* !LOGGER_HPP_ */
