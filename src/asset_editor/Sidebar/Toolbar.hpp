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
             * @brief Display the undo button
             * 
             * @param window The window of the Asset Editor
             */
            void displayUndoButton(sf::RenderWindow &window);

            /**
             * @brief Display the redo button
             * 
             * @param window The window of the Asset Editor
             */
            void displayRedoButton(sf::RenderWindow &window);

            /**
             * @brief Display the save button
             * 
             * @param window The window of the Asset Editor
             */
            void displaySaveButton(sf::RenderWindow &window);

            /**
             * @brief Display the delete button
             * 
             * @param window The window of the Asset Editor
             */
            void displayDeleteButton(sf::RenderWindow &window);
            
            /**
             * @brief Display the move button
             * 
             * @param window The window of the Asset Editor
             */
            void displayMoveButton(sf::RenderWindow &window);

            /**
             * @brief Display the zoom button
             * 
             * @param window The window of the Asset Editor
             */
            void displayZoomButton(sf::RenderWindow &window);
            
            /**
             * @brief Display the dezoom button
             * 
             * @param window The window of the Asset Editor
             */
            void displayDezoomButton(sf::RenderWindow &window);

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
    };
}

#endif /* !TOOLBAR_HPP_ */
