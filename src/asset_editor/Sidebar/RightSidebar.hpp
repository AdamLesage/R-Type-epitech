/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RightSidebar
*/

#ifndef RIGHTSIDEBAR_HPP_
#define RIGHTSIDEBAR_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <array>


namespace Edition {
    /**
     * @brief Right Sidebar of the Asset Editor
     * 
     * This sidebar will be used to display different assets and components that can be added to the scene
     * 
     * Components will be given to different entities in the scene
     */
    class RightSidebar {
        public:
            /**
             * @brief Construct a new Right Sidebar object
             */
            RightSidebar();

            /**
             * @brief Destroy the Right Sidebar object
             */
            ~RightSidebar();

            /**
             * @brief Draw the sidebar
             * 
             * @param window The window of the Asset Editor
             */
            void drawContainer(sf::RenderWindow &window);

            /**
             * @brief Draw the close button of the sidebar
             * 
             * @param window The window of the Asset Editor
             */
            void drawCloseContainer(sf::RenderWindow &window);

            /**
             * @brief Draw the sidebar
             * 
             * @param window The window of the Asset Editor
             */
            void draw(sf::RenderWindow &window);

            /**
             * @brief Set the current sidebar selection
             * 
             * @param selection The selection to set
             */
            void setCurrentSidebarSelection(const std::string &selection) { _currentSidebarSelection = selection; }

            /**
             * @brief Get the current sidebar selection
             * 
             * @return std::string The current selection
             */
            std::string getCurrentSidebarSelection() const { return _currentSidebarSelection; }

            /**
             * @brief Displat tabs selections in the sidebar
             * 
             * @param window The window of the Asset Editor
             */
            void displayTabSelections(sf::RenderWindow &window);

        protected:
            /**
             * @brief The current selection in the sidebar: "Assets", "Components"
             */
            std::string _currentSidebarSelection;
            bool _isSidebarOpen;
            std::array<std::string, 2> _sidebarSelections = {"Assets", "Components"};
        private:
            /**
             * @brief Toggle the sidebar open or close
             */
            void toggleSidebar();
    };
}

#endif /* !RIGHTSIDEBAR_HPP_ */
