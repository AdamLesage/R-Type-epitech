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

void Edition::CommandManager::executeCommand(std::shared_ptr<ICommand> command)
{
    command->execute();
    undoStack.push(std::move(command));

    // Clear the redo stack
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void Edition::CommandManager::undo()
{
    if (undoStack.empty()) { // Nothing to undo
        return;
    }

    auto command = std::move(undoStack.top());
    undoStack.pop();
    command->undo();
    redoStack.push(std::move(command));
}

void Edition::CommandManager::redo()
{
    if (redoStack.empty()) { // Nothing to redo
        return;
    }

    auto command = std::move(redoStack.top());
    redoStack.pop();
    command->execute();
    undoStack.push(std::move(command));
}

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