/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Logger
*/

#include "Logger.hpp"

using namespace RType;

Logger::~Logger() {}

void Logger::log(LogType type, const char *message, ...)
{
    va_list args;
    va_start(args, message);

    const char* reset = "\033[0m";
    const char* yellow = "\033[33m";
    const char* purple = "\033[35m";
    const char* red = "\033[31m";
    const char* blue = "\033[34m";

    switch (type) {
    case LogType::INFO:
        printf("%s[INFO] %s", yellow, reset);
        break;
    case LogType::WARN:
        printf("%s[WARN] %s", purple, reset);
        break;
    case LogType::ERROR:
        printf("%s[ERROR] %s", red, reset);
        break;
    case LogType::DEBUG:
        printf("%s[DEBUG] %s", blue, reset);
        break;
    }

    vprintf(message, args);
    printf("\n");

    va_end(args);
}
