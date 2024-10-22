/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** GameMetrics
*/

#ifndef GAMEMETRICS_HPP_
#define GAMEMETRICS_HPP_

#include <SFML/Graphics.hpp>

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
        void displayCPU(sf::RenderWindow& window);

        /**
         * @brief Display Memory used 
         */
        void displayMemory();

        /**
         * @brief Display player position
         */
        void displayPlayerPosition();
};

#endif /* !GAMEMETRICS_HPP_ */
