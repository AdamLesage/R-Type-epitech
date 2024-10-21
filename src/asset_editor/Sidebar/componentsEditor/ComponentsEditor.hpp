/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ComponentsEditor
*/

#ifndef COMPONENTSEDITOR_HPP_
#define COMPONENTSEDITOR_HPP_

#include "../../history/Asset.hpp"
#include <memory>
#include "Input.hpp"
#include "InputNumber.hpp"
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace Edition {
    /**
     * @brief A class used for editing the attributes of assets.
     * 
     * The ComponentsEditor class provides functionality to modify 
     * various properties of an asset, such as size, position, and pattern. 
     * It interacts with the user to update the selected entity and renders 
     * the necessary UI components for asset editing.
     */
    class ComponentsEditor {
        public:
            ComponentsEditor();
            ~ComponentsEditor();

            /**
             * @brief Updates the currently selected asset with new attributes.
             * 
             * @param asset The asset to be modified.
             */
            void updateSelectedEntity(std::shared_ptr<Edition::Asset> asset);

            /**
             * @brief Displays the editor UI on the provided window.
             * 
             * @param window The render window where the UI is displayed.
             */
            void display(std::shared_ptr<sf::RenderWindow> window);

            /**
             * @brief Handles user input events for the editor.
             * 
             * @param event The event to handle, typically user input such as keyboard or mouse actions.
             */
            void handleInput(const sf::Event &event);

            private:
            /**
             * @brief Displays the title of a category in the specified position.
             * 
             * @param window The render window where the title is displayed.
             * @param title The title text to be displayed.
             * @param posX The X coordinate for the position of the title.
             * @param posY The Y coordinate for the position of the title.
             */
            void displayCategoryTitle(std::shared_ptr<sf::RenderWindow> window, std::string title, float posX, float posY);
            std::shared_ptr<Edition::Asset> _asset;
            sf::Font font;
            std::unique_ptr<Input> label;
            std::unique_ptr<InputNumber> posX;
            std::unique_ptr<InputNumber> posY;
            std::unique_ptr<InputNumber> sizeX;
            std::unique_ptr<InputNumber> sizeY;
            std::unique_ptr<InputNumber> rotation;
    };
}

#endif /* !COMPONENTSEDITOR_HPP_ */
