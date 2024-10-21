/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetSelector
*/

#ifndef ASSETSELECTOR_HPP_
#define ASSETSELECTOR_HPP_

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <algorithm>
#include "../Sidebar/selectBar/SelectBar.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace Edition {
    /**
     * @brief the AssetSelector is used to find and select asset
     */
    class AssetSelector {
        public:
            AssetSelector(std::shared_ptr<sf::RenderWindow> window);
            ~AssetSelector();
            /**
             * @brief display the AssetSelector on the window
             * 
             * @param window the window of the assetEditor
             */
            void display();
            /**
             * @brief handle the scroll on the AssetSelector;
             * @param event the event of the window
             */
            void handleEvent(const sf::Event& event);
        protected:
        private:
            /**
             * @brief load the assets of the project
             * 
             * @param assetPath the directory path
             */
            void findAndLoadAsset(const std::string &assetPath);

            std::unordered_map<std::string, std::unordered_map<std::string, sf::Texture*>> assetMap;
            std::array<std::string, 3> extensions = {".png", ".jpg", ".jpeg"};
            sf::View AssetSelectorView;
            float scrollOffset = 0;
            const float scrollSpeed = 20;
            float maxScrollOffset = 0;
            std::unique_ptr<SelectBar> selectBar;
            std::shared_ptr<sf::RenderWindow> _window;
    };
}

#endif /* !ASSETSELECTOR_HPP_ */
