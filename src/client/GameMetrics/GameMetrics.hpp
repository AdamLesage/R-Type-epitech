/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** GameMetrics
*/

#ifndef GAMEMETRICS_HPP_
    #define GAMEMETRICS_HPP_

    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include <fstream>
    #include <string>
    #ifdef _WIN32
        #include <windows.h>
        #include <psapi.h>
    #elif __linux__
        #include <sys/resource.h>
        #include <sys/sysinfo.h>
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        #define PATH_SEPARATOR "\\"
    #else
        #define PATH_SEPARATOR "/"
    #endif


class GameMetrics {
    public:
        /**
         * @brief Default constructor
         */
        GameMetrics();

        /**
         * @brief Default destructor
         */
        ~GameMetrics();

        /**
         * @brief Display game Frame Per Second 
         */
        void displayFPS(sf::RenderWindow& window);

        /**
         * @brief Display CPU information 
         */
        void displayCPU();

        /**
         * @brief Display Memory used 
         */
        void displayMemory(sf::RenderWindow& window);

        /**
         * @brief Display player position
         */
        void displayPlayerPosition();

        /**
         * @brief Display the latency between server and clients in MS
         *
         * @param sf::RenderWindow& window
         * @param float latency
         */
        void displayLatency(sf::RenderWindow& window, float& latency);
    private:
        std::size_t getMemoryUsage();
};

#endif /* !GAMEMETRICS_HPP_ */
