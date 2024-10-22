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
        #include <comdef.h>
        #include <Wbemidl.h>
        #pragma comment(lib, "wbemuuid.lib")
    #elif __linux__
        #include <sys/resource.h>
        #include <sys/sysinfo.h>
        #include <fstream>
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
         */
        void displayFPS(sf::RenderWindow& window);

        /**
         * @brief Display CPU information 
         */
        void displayCPU();

        /**
         * @brief Display Memory used
         * 
         * @param window
         */
        void displayMemory(sf::RenderWindow& window);

        /**
         * @brief Display player position
         */
        void displayPlayerPosition();

        /**
         * @brief Display GPU usage
         * 
         * @param window
         */
        void displayGpuUsage(sf::RenderWindow& window);
    private:
        std::size_t getMemoryUsage();
};

#endif /* !GAMEMETRICS_HPP_ */
