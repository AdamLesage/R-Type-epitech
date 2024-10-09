/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
    #define LOGGER_HPP_

    #include <iostream>
    #include <stdio.h>
    #include <stdarg.h>

namespace RType {
    class Logger {
    public:
        enum LogType {
            INFO,
            WARN,
            ERROR,
            DEBUG
        };

        /**
         * @brief Construct a new Logger object
         *
         */
        Logger() = default;

        /**
         * @brief Destroy the Logger object
         *
         */
        ~Logger();

        /**
         * @brief log a message with a type
         * @param type
         * @param message
         * @param ...
         */
        void log(LogType type, const char *message, ...);
    };
}  // namespace RType
#endif /* !LOGGER_HPP_ */
