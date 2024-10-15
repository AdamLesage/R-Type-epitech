/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Toolbar
*/

#ifndef TOOLBAR_HPP_
#define TOOLBAR_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ToolbarButton.hpp"
#include <string>

namespace Edition {
    /**
     * @brief Toolbar of the Asset Editor
     * 
     * This toolbar will be used to display different tools that can be used to edit the scene
     * 
     * Tools will be used to modify the scene
     */
    class Toolbar {
        public:
            /**
             * @brief Construct a new Toolbar object
             */
            Toolbar();

            /**
             * @brief Destroy the Toolbar object
             */
            ~Toolbar();

            /**
             * @brief Display every toolbar buttons
             * 
             * This will display every toolbar buttons that are in the toolbar
             * 
             * @param window The window of the Asset Editor
             */
            void displayToolbarButtons(sf::RenderWindow &window);


            /**
             * @brief Display the toolbar container
             * 
             * This will display the toolbar container that will contain all the tools
             * 
             * @param window The window of the Asset Editor
             */
            void displayToolbarContainer(sf::RenderWindow &window);

            /**
             * @brief Draw the toolbar
             * 
             * @param window The window of the Asset Editor
             */
            void draw(sf::RenderWindow &window);
        protected:
        private:
            std::vector<ToolbarButton> _toolbarButtons;
    };
}

#endif /* !TOOLBAR_HPP_ */
