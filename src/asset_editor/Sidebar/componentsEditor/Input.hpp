/*
** EPITECH PROJECT, 2024
** B-OOP-400-NAN-4-1-Edition-adam.lesage
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace Edition {
    class Input {
        public:
            /**
             * @brief Construct a new Input object
             * 
             * @param size The size of the input field
             * @param pos The position of the input field
             * @param title The title or label of the input field (default is an empty string)
             */
            Input(sf::Vector2f size, sf::Vector2f pos, std::string title = "");
            
            /**
             * @brief Destroy the Input object
             */
            ~Input();

            /**
             * @brief Check user input when the input field is selected
             * 
             * @param event The event to check
             * @return true if the input is valid, false otherwise
             */
            virtual bool checkInput(const sf::Event &event);
            
            /**
             * @brief Display the input field and handle user input
             * 
             * @param window The render window where the input field is displayed
             */
            virtual void displayInput(std::shared_ptr<sf::RenderWindow> window);
            
            /**
             * @brief Get the current value of the user input
             * 
             * @return The string value of the user input
             */
            std::string getInput() const;

            /**
             * @brief Manage mouse click on the input field to select it
             * 
             * @param event The event to check for mouse clicks
             */
            void checkClick(const sf::Event &event);
            
            /**
             * @brief Set the value of the user input
             * 
             * @param input The string value to set as the user input
             */
            void setInput(std::string input);

        protected:
            /**
             * @brief Update the displayed text in the input field
             */
            void updateText();
            std::string _input;
            sf::Vector2f _size;
            sf::Vector2f _pos;
            std::unique_ptr<sf::RectangleShape> _back;
            sf::Text _inputText;
            sf::Text _titleText;
            sf::Font _font;
            bool fontLoaded;
            bool _typing;
        private:
    };
}

#endif /* !INPUT_HPP_ */
