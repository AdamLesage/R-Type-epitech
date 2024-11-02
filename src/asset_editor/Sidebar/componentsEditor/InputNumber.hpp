/*
** EPITECH PROJECT, 2024
** B-OOP-400-NAN-4-1-raytracer-adam.lesage
** File description:
** InputNumber
*/

#ifndef INPUTNUMBER_HPP_
#define INPUTNUMBER_HPP_

#include "Input.hpp"

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace Edition {
    class InputNumber : public virtual Input {
        public:
            /**
             * @brief Construct a new InputNumber object
             *
             * @param size The size of the input field
             * @param pos The position of the input field
             * @param title The title or label of the input field (default is an empty string)
             */
            InputNumber(sf::Vector2f size, sf::Vector2f pos, std::string title = "");
            ~InputNumber();
            /**
             * @brief Check user input when the input field is selected
             *
             * @param event The event to check
             * @return true if the input is valid, false otherwise
             */
            bool checkInput(const sf::Event& event) override;

        protected:
        private:
    };
}; // namespace Edition

#endif /* !INPUTNUMBER_HPP_ */
