/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetSelector
*/

#include "AssetSelector.hpp"

AssetSelector::AssetSelector()
{
    std::string assetPath = std::string("assets");    
    findAndLoadAsset(assetPath);
    // for (auto& it: this->assetMap)
        // std::cout << it.first << std::endl;
}

AssetSelector::~AssetSelector()
{
}

void AssetSelector::findAndLoadAsset(const std::string &assetPath)
{
    // std::cout << std::endl << "-----Enter in: " << assetPath << " Folder-----" << std::endl << std::endl;
    for (const auto & entry : std::filesystem::directory_iterator(assetPath)) {
        std::string str = entry.path();
        size_t found = 0;
        found = str.find_last_of("/\\");
        std::string folder = str.substr(0,found);
        std::string file = str.substr(found+1);
        if (entry.is_directory()) {
            findAndLoadAsset(assetPath + PATH_SEPARATOR + file);
        } else {
            if (std::find(this->extensions.begin(), this->extensions.end(), entry.path().extension()) != this->extensions.end()) {
                // std::cout << " file: " << entry.path() << std::endl;
                sf::Texture texture;
                texture.loadFromFile(entry.path());
                this->assetMap[assetPath][entry.path()] = texture;
            }
        }
    }
}
