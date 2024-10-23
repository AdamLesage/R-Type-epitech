/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ICommand
*/

#ifndef ICOMMAND_HPP_
#define ICOMMAND_HPP_

#include <memory>
#include <iostream>

namespace Edition {

    /**
     * @brief Command Interface
     * 
     * This interface will be used to create commands
     */
    class ICommand {
        public:
            virtual ~ICommand() = default;

            /**
             * @brief Execute the command
             */
            virtual void execute() = 0;

            /**
             * @brief Undo the command
             */
            virtual void undo() = 0;

            /**
             * @brief Redo the command
             */
            virtual void redo() = 0;

        protected:
        private:
    };
}

#endif /* !ICOMMAND_HPP_ */