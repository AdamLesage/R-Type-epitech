/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** *
*/

#ifndef IMEDIATOR_HPP_
#define IMEDIATOR_HPP_

#include <string>

namespace RType {
    class IMediator {
        public:
            virtual ~IMediator() = default;
            /**
             * @brief Notify the engine of an event.
             *
             * @param sender The sender of the event.
             * @param event The event to notify.
             */
            virtual void notify(std::string sender, const std::string& event) = 0;

            /**
             * @brief Set the string for the game selected
             * 
             * @param gameSelected the game selected
             */
            virtual void setGameSelected(const std::string& gameSelected) = 0;

        protected:
        private:
    };
} // namespace RType

#endif /* !IMEDIATOR_HPP_ */
