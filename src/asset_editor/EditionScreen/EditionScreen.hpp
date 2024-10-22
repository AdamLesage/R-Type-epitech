/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** EditionScreen
*/

#ifndef EDITIONSCREEN_HPP_
#define EDITIONSCREEN_HPP_

#include "../history/Asset.hpp"
#include "../history/MoveAsset.hpp"
#include "../history/AddAsset.hpp"
#include "../history/RemoveAsset.hpp"
#include "../history/CommandManager.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

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
            std::shared_ptr<Edition::Asset> handleEvent(const sf::Event &event);

            /**
             * @brief Display dialog to save the scene
             * 
             * @param window The window of the Asset Editor
             * @return true if the user saved the scene, false if the dialog was closed
             */
            bool displaySaveDialog(std::shared_ptr<sf::RenderWindow> window);

            /**
             * @brief Save the scene
             * 
             * @param event The event to handle
             */
            void retrieveInputSaveScene(const sf::Event &event);

            /**
             * @brief Save the scene in a cfg file with the given name
             * 
             * @param sceneName The name of the scene to load
             */
            void saveScene(const std::string &sceneName);

            /**
             * @brief The command manager
             */
            CommandManager commandManager;
        private:
            sf::RectangleShape _centralArea;
            sf::Text _inputSaveText;
    };
}

#endif /* !EDITIONSCREEN_HPP_ */
