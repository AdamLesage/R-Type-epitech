/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** CommandManager
*/

#ifndef COMMANDMANAGER_HPP_
#define COMMANDMANAGER_HPP_

#include <iostream>
#include <memory>

#include "ICommand.hpp"
#include "Asset.hpp"

namespace Edition {

    /**
     * @brief Command Manager of the Asset Editor
     * 
     * This class will be used to manage the commands of the Asset Editor
     */
    class CommandManager {
        public:
            /**
             * @brief Construct a new Command Manager object
             */
            CommandManager();

            /**
             * @brief Destroy the Command Manager object
             */
            ~CommandManager();

            /**
             * @brief Execute a command
             * 
             * @param command The command to execute
             */
            void createAsset(std::shared_ptr<Edition::Asset> asset);

            /**
             * @brief Undo the last command
             */
            void undo();

            /**
             * @brief Redo the last command
             */
            void redo();

            /**
             * @brief Get the undo vector
             * 
             * @return std::vector<std::shared_ptr<ICommand>> The undo vector
             */
            std::vector<std::shared_ptr<Edition::Asset>> getUndoAssets() const { return _undoAssets; }

            /**
             * @brief Clear the redo vector
             */
            void clearRedoAssets() { _redoAssets.clear(); }

            /**
             * @brief Clear the undo vector
             */
            void clearUndoAssets() { _undoAssets.clear(); }

            /**
             * @brief Get the redo vector
             * 
             * @return std::vector<std::shared_ptr<ICommand>> The redo vector
             */
            std::vector<std::shared_ptr<Edition::Asset>> getRedoAssets() const { return _redoAssets; }

            /**
             * @brief Set the undo vector from another vector (will be called from load scene function)
             * 
             * @param undoAssets The undo vector to set
             */
            void setUndoAssets(std::vector<std::shared_ptr<Edition::Asset>> undoAssets) { _undoAssets = undoAssets; }

        protected:
        private:
            /**
             * @brief The assets of the scene
             */
            std::vector<std::shared_ptr<Edition::Asset>> _undoAssets;

            /**
             * @brief The redo assets of the scene
             */
            std::vector<std::shared_ptr<Edition::Asset>> _redoAssets;
    };
}

#endif /* !COMMANDMANAGER_HPP_ */
