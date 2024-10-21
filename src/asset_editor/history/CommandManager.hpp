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
#include <stack>

#include "ICommand.hpp"

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
            void executeCommand(std::shared_ptr<ICommand> command);

            /**
             * @brief Undo the last command
             */
            void undo();

            /**
             * @brief Redo the last command
             */
            void redo();

        protected:
        private:
            /**
             * @brief Stack of commands
             */
            std::stack<std::shared_ptr<ICommand>> undoStack;

            /**
             * @brief Stack of commands
             */
            std::stack<std::shared_ptr<ICommand>> redoStack;
    };
}

#endif /* !COMMANDMANAGER_HPP_ */
