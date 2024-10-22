/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** SaveScene
*/

#include "SaveScene.hpp"

Edition::SaveScene::SaveScene(std::string scenePath, std::vector<std::shared_ptr<Asset>> assets)
{
    _assets = assets;
    _scenePath = scenePath;
}

Edition::SaveScene::~SaveScene()
{
}
void Edition::SaveScene::save()
{
    std::ofstream outFile(_scenePath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + _scenePath);
    }

    outFile << "scene: {" << std::endl;
    outFile << "\tentities: [" << std::endl;

    for (auto& it : _assets) {
        outFile << "\t\t{" << std::endl;

        this->saveEntityCode(outFile, it);

        if (it != _assets.back()) {
            outFile << "\t\t}," << std::endl;
        } else {
            outFile << "\t\t}" << std::endl;
        }
    }

    outFile << "\t]" << std::endl;
    outFile << "}" << std::endl;

    outFile.close();
}

void Edition::SaveScene::saveEntityCode(std::ofstream &outFile, std::shared_ptr<Asset> asset)
{
    outFile << "\t\t\tcode: " << asset->getEntityCode() << "," << std::endl;
}