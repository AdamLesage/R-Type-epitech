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
#include "../assetSelector/AssetSelector.hpp"

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
            void drawContainer(std::shared_ptr<sf::RenderWindow> window);

            /**
             * @brief Draw the close button of the sidebar
             * 
             * @param window The window of the Asset Editor
             */
            void drawCloseContainer(std::shared_ptr<sf::RenderWindow> window);

            /**
             * @brief Draw the sidebar
             * 
             * @param window The window of the Asset Editor
             */
            void draw(std::shared_ptr<sf::RenderWindow> window);

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
            void displayTabSelections(std::shared_ptr<sf::RenderWindow> window);

            /**
             * @brief handle the scroll on the RightSideBar;
             * 
             * @param event the event of the window
             */
            void handleEvent(const sf::Event& event);
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
            std::unique_ptr<AssetSelector> assetSelector;
    };
}

#endif /* !RIGHTSIDEBAR_HPP_ */
