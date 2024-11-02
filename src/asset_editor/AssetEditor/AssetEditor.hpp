/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetEditor
*/

#ifndef ASSETEDITOR_HPP_
#define ASSETEDITOR_HPP_

#include "../Sidebar/RightSidebar.hpp"
#include "../Sidebar/Toolbar.hpp"
#include "../EditionScreen/EditionScreen.hpp"
#include "../history/CommandManager.hpp"
#include "../history/AddAsset.hpp"
#include "../history/RemoveAsset.hpp"
#include "../history/MoveAsset.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

namespace Edition {
    class AssetEditor {
        public:
            /**
             * @brief Construct a new Asset Editor object
             */
            AssetEditor();

            /**
             * @brief Destroy the Asset Editor object
             */
            ~AssetEditor();

            /**
             * @brief Run the Asset Editor
             */
            void run();

            /**
             * @brief Handles toolbar event such as button clicks
             *
             * This function will handle actions such as undo, redo, save, delete, move, zoom and dezoom
             *
             * @param event The SFML event to process.
             */
            void handleToolbarEvents(const sf::Event& event);

            /**
             * @brief Display toolbar events
             */
            void displayToolbarEvents();

        protected:
        private:
            /**
             * @brief Handles drag-and-drop events for textures.
             *
             * Updates the rectangle shape position based on mouse events
             * and manages the texture loading and unloading.
             *
             * @param event The SFML event to process.
             * @param texturePath The path of the texture to be dragged.
             */
            void manageDragAndDrop(sf::Event& event, std::string& texturPath);

            std::shared_ptr<sf::RenderWindow> _window;
            std::shared_ptr<RightSidebar> _rightSidebar;
            std::unique_ptr<sf::Texture> mouseTexture;
            std::string mousePathTexture;
            std::unique_ptr<sf::RectangleShape> mousePickRect;
            Toolbar _toolbar;
            EditionScreen _editionScreen;
            size_t _lastEntityCode;
    };
} // namespace Edition

#endif /* !ASSETEDITOR_HPP_ */
