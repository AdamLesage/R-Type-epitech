/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Logger
*/

#include "Logger.hpp"

using namespace RType;

#ifdef _WIN32
#include <windows.h>
#endif

void Logger::log(LogType type, const char* message, ...) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    va_list args;
    va_start(args, message);

    const char* logPrefix = NULL; // Remplace nullptr par NULL

    switch (static_cast<int>(type)) {
    case static_cast<int>(RType::Logger::RTYPEINFO):
        logPrefix = "[INFO] ";
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#endif
        break;
    case static_cast<int>(RType::Logger::RTYPEWARN):
        logPrefix = "[WARN] ";
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#endif
        break;
    case static_cast<int>(RType::Logger::RTYPEERROR):
        logPrefix = "[ERROR] ";
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
#endif
        break;
    case static_cast<int>(RType::Logger::RTYPEDEBUG):
        logPrefix = "[DEBUG] ";
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#endif
        break;
    }

    if (logPrefix != NULL) {
        printf("%s", logPrefix);
    }

    vprintf(message, args);
    printf("\n");

#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, 7); // Reset couleur par défaut (gris clair)
#endif

    va_end(args);
}
