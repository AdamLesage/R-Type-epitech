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
        private:
            std::shared_ptr<Edition::Asset> _asset;
    };
}

#endif /* !COMPONENTSEDITOR_HPP_ */
