/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** MoveAsset
*/

#include "MoveAsset.hpp"

Edition::MoveAsset::MoveAsset(std::shared_ptr<Asset> asset, int dx, int dy)
{
    _asset = asset;
    _dx = dx;
    _dy = dy;
}

Edition::MoveAsset::~MoveAsset()
{
}

void Edition::MoveAsset::execute()
{
    _asset->move(_dx, _dy);
}

void Edition::MoveAsset::undo()
{
    _asset->move(-_dx, -_dy);
}

void Edition::MoveAsset::redo()
{
    _asset->move(_dx, _dy);
}