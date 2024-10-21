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
