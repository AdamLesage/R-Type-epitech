/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AddAsset
*/

#include "AddAsset.hpp"

Edition::AddAsset::AddAsset(std::vector<std::shared_ptr<Asset>>& assets, std::shared_ptr<Asset> asset)
{
    _assets = assets;
    _asset = asset;
}

Edition::AddAsset::~AddAsset()
{
}

void Edition::AddAsset::execute()
{
    _assets.push_back(_asset);
}

void Edition::AddAsset::undo()
{
    _assets.pop_back();
}

void Edition::AddAsset::redo()
{
    _assets.push_back(_asset);
}
