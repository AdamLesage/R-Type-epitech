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

        Logger() = default;
        ~Logger();

        void log(LogType type, const char *message, ...);
    };
}  // namespace RType
#endif /* !LOGGER_HPP_ */
