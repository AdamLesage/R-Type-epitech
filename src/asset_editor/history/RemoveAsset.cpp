/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RemoveAsset
*/

#include "RemoveAsset.hpp"

Edition::RemoveAsset::RemoveAsset(std::vector<std::shared_ptr<Asset>>& assets)
{
    _assets = assets;
    _asset = nullptr;
}

Edition::RemoveAsset::~RemoveAsset()
{
}

void Edition::RemoveAsset::execute()
{
    if (_assets.empty()) // No asset to remove
        return;

    _asset = _assets.back();
    _assets.pop_back();
}

void Edition::RemoveAsset::undo()
{
    if (_asset == nullptr) // No asset to add
        return;

    _assets.push_back(_asset);
}
