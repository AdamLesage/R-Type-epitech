/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetEditor
*/

#ifndef ASSETEDITOR_HPP_
#define ASSETEDITOR_HPP_

#include <iostream>
#include "../Sidebar/RightSidebar.hpp"
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

        protected:
        private:
            sf::RenderWindow _window;
            std::shared_ptr<RightSidebar> _rightSidebar;
    };
}

#endif /* !ASSETEDITOR_HPP_ */
