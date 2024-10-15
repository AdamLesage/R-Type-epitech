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
#include <filesystem>
#include <iostream>
#include <array>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif
class AssetSelector {
    public:
        AssetSelector();
        ~AssetSelector();
        
    protected:
    private:
        void findAndLoadAsset(const std::string &assetPath);
        std::unordered_map<std::string, std::unordered_map<std::string, sf::Texture>> assetMap;
        std::array<std::string, 3> extensions = {".png", ".jpg", ".jpeg"};
};

#endif /* !ASSETSELECTOR_HPP_ */
