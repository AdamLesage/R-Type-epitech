/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** SelectBar
*/

#ifndef SELECTBAR_HPP_
#define SELECTBAR_HPP_

#include <string>
#include <array>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
    #define NOMINMAX
    #include <windows.h>
    #define LIB_EXTENSION ".dll"
    #define PATH_SEPARATOR "\\"
#else
    #include <dlfcn.h>
    #define LIB_EXTENSION ".so"
    #define PATH_SEPARATOR "/"
#endif

namespace Edition
{
    /**
     * @brief A class representing a selection bar (selectBar), which allows the user to choose from a list of options.
     */
    class SelectBar {
        public:
            /**
             * @brief Constructs a SelectBar with given options and positioning.
             * 
             * @param selectOption A vector of strings representing the available options in the selection bar.
             * @param x The X-coordinate for the position of the selection bar.
             * @param y The Y-coordinate for the position of the selection bar.
             * @param maxWidth The maximum width of the selection bar.
             */
            SelectBar(std::vector<std::string> selectOption, float x, float y, int maxWidth);
            /**
             * @brief Destructor for the SelectBar class.
             */
            ~SelectBar();

            /**
             * @brief display the selectBar on the window
             * 
             * @param window the window
             */
            void display(std::shared_ptr<sf::RenderWindow> window);
            /**
             * @brief Retrieves the available options in the selection bar.
             * 
             * @return A vector containing the options as strings.
             */
            std::vector<std::string> getSelectOption();
            /**
             * @brief Gets the height of the selection bar.
             * 
             * @return The height of the selection bar in pixels.
             */
            int getHeightSelectBar();
            /**
             * @brief Finds the index of the currently selected option.
             * 
             * @return The index of the selected option (integer).
             */
            int findSelectedIndex();
            /**
             * @brief Finds the currently selected option in the selection bar.
             * 
             * @return The selected option as a string.
             */
            std::string findSelectedOption();
            /**
             * @brief Handles events for the selection bar, such as user interactions.
             * 
             * @param event SFML event to be processed (keyboard, mouse, etc.).
             */
            bool handleEvent(const sf::Event event);
        private:
            /**
             * @brief A vector containing the list of available options as strings in the selection bar.
             */
            std::vector<std::string> _selectionOption;

            /**
             * @brief A vector of rectangle shapes representing the buttons for each selection option.
             */
            std::vector<sf::RectangleShape> _selectionButton;

            /**
             * @brief A vector of text objects displaying the text for each selection option.
             */
            std::vector<sf::Text> _selectionText;

            /**
             * @brief The index of the currently selected option in the selection bar.
             */
            std::size_t selectedOptionIndex = 0;

            /**
             * @brief The font used for rendering the text of the selection options.
             */
            sf::Font font;

            /**
             * @brief The height of the selection bar.
             */
            float height;
    };
} // namespace Edition

#endif /* !SELECTBAR_HPP_ */
