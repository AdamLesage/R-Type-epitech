#ifndef SELECTBUTTON_HPP
#define SELECTBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

namespace Edition {
    class SelectButton {
    public:
        /** @brief Constructor for the SelectButton class.
         *  @param position Position of the button.
         *  @param size Size of the button.
         *  @param options List of string options to display.
         */
        SelectButton(const sf::Vector2f& position, const sf::Vector2f& size, const std::vector<std::string>& options);

        /** @brief Handle user input, such as mouse clicks.
         *  @param event The SFML event to process.
         *  @param window Reference to the render window.
         */
        void handleInput(const sf::Event& event);

        /** @brief Display the button and its options in the window.
         *  @param window Reference to the render window.
         */
        void display(sf::RenderWindow& window);

        /** @brief Get the selected option as a string.
         *  @return The selected option.
         */
        std::string getSelectedOption() const;

        /** @brief Set the position of the element.
         *  @param pos The new position as an sf::Vector2f.
         */
        void setPosition(sf::Vector2f pos);
    private:
        sf::RectangleShape box;
        std::vector<std::string> options;
        std::vector<sf::Text> optionTexts;
        std::vector<sf::Text> optionBack;
        std::vector<sf::RectangleShape> backOptions;
        sf::Font font;
        int selectedOption;
        bool isDropdownOpen;

        /** @brief Toggle the dropdown menu (open/close).
         */
        void toggleDropdown();
    };
}

#endif
