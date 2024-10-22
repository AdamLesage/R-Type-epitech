/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** CommandManager
*/

#include "CommandManager.hpp"

Edition::CommandManager::CommandManager()
{
}

Edition::CommandManager::~CommandManager()
{
}

void Edition::CommandManager::createAsset(std::shared_ptr<Edition::Asset> asset)
{
    _undoAssets.push_back(asset);

    // Clear the redo 
    _redoAssets.clear();
}

void Edition::CommandManager::undo()
{
    if (_undoAssets.empty()) { // Nothing to undo
        return;
    }

    auto asset = std::move(_undoAssets.back());
    _undoAssets.pop_back();
    _redoAssets.push_back(asset);
}

void Edition::CommandManager::redo()
{
    if (_redoAssets.empty()) { // Nothing to redo
        return;
    }

    auto asset = std::move(_redoAssets.back());
    _redoAssets.pop_back();
    _undoAssets.push_back(asset);
}

// std::vector<std::shared_ptr<Edition::Asset>> Edition::CommandManager::getUndoAssetsVector() const
// {
//     std::vector<std::shared_ptr<Edition::Asset>> assets;
//     std::stack<std::shared_ptr<Edition::Asset>> tempStack = _undoAssets;

//     while (!tempStack.empty()) {
//         assets.push_back(tempStack.top());
//         tempStack.pop();
//     }
//     return assets;
// }

// std::vector<std::shared_ptr<Edition::Asset>> Edition::CommandManager::getRedoAssetsVector() const
// {
//     std::vector<std::shared_ptr<Edition::Asset>> assets;
//     std::stack<std::shared_ptr<Edition::Asset>> tempStack = _redoAssets;

//     while (!tempStack.empty()) {
//         assets.push_back(tempStack.top());
//         tempStack.pop();
//     }
//     return assets;
// }

/* Example of use
int main() {
    std::vector<std::shared_ptr<Asset>> assets;
    CommandManager commandManager;

    auto asset1 = std::make_shared<Asset>(0, 0);
    commandManager.executeCommand(std::make_unique<AddAssetCommand>(assets, asset1));

    asset1->print();

    commandManager.executeCommand(std::make_unique<MoveAssetCommand>(asset1, 5, 5));
    asset1->print();

    commandManager.undo();
    asset1->print();

    commandManager.redo();
    asset1->print();

    commandManager.executeCommand(std::make_unique<RemoveAssetCommand>(assets));

    commandManager.undo();
    asset1->print();

    return 0;
}
*/