/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** EditionScreen
*/

#ifndef EDITIONSCREEN_HPP_
#define EDITIONSCREEN_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

namespace Edition {

    /**
     * @brief Edition Screen of the Asset Editor
     * 
     * This screen will be used to display the scene and the assets
     * 
     * The user will be able to drag and drop assets in the scene
     */
    class EditionScreen {
        public:
            /**
             * @brief Construct a new Edition Screen object
             */
            EditionScreen();

            /**
             * @brief Destroy the Edition Screen object
             */
            ~EditionScreen();

            /**
             * @brief Draw the Edition Screen
             * 
             * @param window The window of the Asset Editor
             */
            void draw(sf::RenderWindow &window);

            /**
             * @brief Handle the events of the Edition Screen
             * 
             * @param event The event to handle
             */
            void handleEvent(const sf::Event &event);

        private:
            sf::RectangleShape _centralArea; // Zone centrale pour le drag and drop
            std::vector<sf::Sprite> _assets; // Les assets en cours de drag and drop
            bool _isDragging; // Indique si un asset est en cours de drag
            sf::Vector2f _dragOffset; // Offset pour le déplacement d'un asset
            int _selectedAssetIndex; // Index de l'asset sélectionné
    };
}

#endif /* !EDITIONSCREEN_HPP_ */
