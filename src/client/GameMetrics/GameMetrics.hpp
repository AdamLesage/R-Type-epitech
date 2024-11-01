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
    #include "../../shared/entities/Entity.hpp"
    #ifdef _WIN32
    #define NOMINMAX
        #include <windows.h>
        #include <psapi.h>
        #include <comdef.h>
        #include <Wbemidl.h>
        #pragma comment(lib, "wbemuuid.lib")
    #elif __linux__
        #include <sys/resource.h>
        #include <sys/sysinfo.h>
        #include <fstream>
    #endif

    #ifdef _WIN32
        #include <pdh.h>
        #pragma comment(lib, "pdh.lib")
    #endif

    #ifdef _WIN32
        extern PDH_HQUERY cpuQuery;
        extern PDH_HCOUNTER cpuTotal;
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        #define PATH_SEPARATOR "\\"
    #else
        #define PATH_SEPARATOR "/"
    #endif


class GameMetrics {
    public:
        struct GpuInfo {
            std::string model;
            std::size_t vramUsed;
            std::size_t vramTotal;
            float temperature;
        };
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
         * 
         * @param window
         */
        void displayFPS(sf::RenderWindow& window);

        /**
         * @brief Display CPU information 
         * 
         * @param window
         */
        void displayCPU(sf::RenderWindow& window);

        /**
         * @brief Display Memory used
         * 
         * @param window
         */
        void displayMemory(sf::RenderWindow& window);

        /**
         * @brief Display player position
         * 
         * @param window
         * @param pos
         */
        void displayPlayerPosition(sf::RenderWindow& window, sf::Vector2f pos);

        /**
         * @brief Display GPU usage
         * 
         * @param window
         */
        void displayGpuUsage(sf::RenderWindow& window);

        /**
         * @brief Display Latency
         * 
         * @param window
         * @param latency
         */
        void displayLatency(sf::RenderWindow& window, float& latency);
    private:
        std::size_t getMemoryUsage();
};

#endif /* !GAMEMETRICS_HPP_ */
