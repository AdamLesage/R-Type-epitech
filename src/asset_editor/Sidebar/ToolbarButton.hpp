/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ToolbarButton
*/

#ifndef TOOLBARBUTTON_HPP_
#define TOOLBARBUTTON_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

namespace Edition {
    /**
     * @brief Toolbar Button of the Asset Editor
     * 
     * This button will be used to display different buttons in the toolbar
     * 
     * Buttons will be used to modify the scene
     */
    class ToolbarButton {
        public:
            /**
             * @brief Construct a new Toolbar Button object
             * 
             * @param buttonIconAssetPath The path to the icon of the button
             * @param position The position of the button
             */
            ToolbarButton(std::string buttonIconAssetPath, sf::Vector2f position);

            /**
             * @brief Destroy the Toolbar Button object
             */
            ~ToolbarButton();

            /**
             * @brief Update the button with hover and click events
             * 
             * @param window The window of the Asset Editor
             * @return true if the button is hovered, false otherwise
             */
            bool update(sf::RenderWindow& window);

            /**
             * @brief Draw the button
             * 
             * @param window The window of the Asset Editor
             */
            void draw(sf::RenderWindow &window);

        protected:
        private:
            std::string _buttonIconAssetPath;
            std::shared_ptr<sf::Texture> _buttonIconTexture;
            sf::Vector2f _position;
            sf::Vector2f _size;
            sf::Color _backgroundColor;
            sf::RectangleShape _backgroundRectangle;
            sf::Sprite _buttonIconSprite;
    };
}

#endif /* !TOOLBARBUTTON_HPP_ */
