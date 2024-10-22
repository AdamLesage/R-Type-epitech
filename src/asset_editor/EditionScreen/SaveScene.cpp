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

        outFile << "\t\t\tcomponents: {" << std::endl;

        this->saveComponentPosition(outFile, it);
        this->saveComponentSize(outFile, it);
        this->saveComponentRotation(outFile, it);

        outFile << "\t\t\t}" << std::endl;

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

void Edition::SaveScene::saveComponentPosition(std::ofstream &outFile, std::shared_ptr<Asset> asset)
{
    try {
        Position position = asset->getComponent<Position>();
        outFile << "\t\t\t\tposition: {x: " << position.x << ", y: " << position.y << "}," << std::endl;
    } catch (const std::exception &e) {
        return; // No position component
    }
}

void Edition::SaveScene::saveComponentSize(std::ofstream &outFile, std::shared_ptr<Asset> asset)
{
    try {
        Size size = asset->getComponent<Size>();
        outFile << "\t\t\t\tsize: {x: " << size.x << ", y: " << size.y << "}," << std::endl;
    } catch (const std::exception &e) {
        return; // No size component
    }
}

void Edition::SaveScene::saveComponentRotation(std::ofstream &outFile, std::shared_ptr<Asset> asset)
{
    try {
        Rotation rotation = asset->getComponent<Rotation>();
        outFile << "\t\t\t\trotation: " << rotation.rotation << "," << std::endl;
    } catch (const std::exception &e) {
        return; // No rotation component
    }
}
