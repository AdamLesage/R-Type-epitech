#include "SelectButton.hpp"

Edition::SelectButton::SelectButton(const sf::Vector2f& position,
                                    const sf::Vector2f& size,
                                    const std::vector<std::string>& options)
    : options(options), selectedOption(-1), isDropdownOpen(false) {

    box.setPosition(position);
    box.setSize(size);
    box.setFillColor(sf::Color(30, 30, 30));
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    this->font.loadFromFile(fontPath);

    for (const auto& option : options) {
        sf::RectangleShape back(size);
        back.setFillColor(sf::Color(30, 30, 30));
        back.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(1);
        backOptions.push_back(back);
        sf::Text text;
        text.setFont(font);
        text.setString(option);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        optionTexts.push_back(text);
    }
}

bool Edition::SelectButton::handleInput(const sf::Event& event) {
    sf::Vector2f mousPos;
    if (event.type == sf::Event::MouseMoved) {
        mousPos.x = static_cast<float>(event.mouseButton.x);
        mousPos.y = static_cast<float>(event.mouseButton.y);
        if (box.getGlobalBounds().contains(mousPos)) {
            toggleDropdown();
        } else if (isDropdownOpen) {
            for (size_t i = 0; i < backOptions.size(); ++i) {
                if (backOptions[i].getGlobalBounds().contains(mousPos)) {

                    selectedOption = i;
                    isDropdownOpen = false;
                    backOptions[i].setFillColor(sf::Color(20, 20, 20));
                } else {
                    backOptions[i].setFillColor(sf::Color(30, 30, 30));
                }
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        mousPos.x = static_cast<float>(event.mouseButton.x);
        mousPos.y = static_cast<float>(event.mouseButton.y);
        if (box.getGlobalBounds().contains(mousPos)) {
            toggleDropdown();
        } else if (isDropdownOpen) {
            for (size_t i = 0; i < optionTexts.size(); ++i) {
                if (backOptions[i].getGlobalBounds().contains(mousPos)) {
                    backOptions[i].setFillColor(sf::Color(100, 100, 100));
                    selectedOption = i;
                    isDropdownOpen = false;
                    return true;
                    break;
                }
            }
        }
    }
    return false;
}

void centerText(sf::RectangleShape& shape, sf::Text& text) {
    const sf::FloatRect textBounds = text.getLocalBounds();
    const sf::Vector2f boxSize     = shape.getSize();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(shape.getPosition().x + boxSize.x / 2.0f, shape.getPosition().y + boxSize.y / 2.0f);
}

void Edition::SelectButton::display(sf::RenderWindow& window) {
    window.draw(box);

    if (selectedOption >= 0) {
        sf::Text selectedText;
        selectedText.setFont(font);
        selectedText.setString(options[selectedOption]);
        selectedText.setCharacterSize(30);
        selectedText.setFillColor(sf::Color::White);
        selectedText.setPosition(box.getPosition().x + 10, box.getPosition().y + 5);
        centerText(box, selectedText);
        window.draw(selectedText);
    }

    if (isDropdownOpen) {
        for (size_t i = 0; i < optionTexts.size(); ++i) {
            sf::Text& text           = optionTexts[i];
            sf::RectangleShape& back = this->backOptions[i];
            text.setPosition(box.getPosition().x, box.getPosition().y + (i + 1) * box.getSize().y);
            back.setPosition(box.getPosition().x, box.getPosition().y + (i + 1) * box.getSize().y);
            centerText(back, text);
            window.draw(back);
            window.draw(text);
        }
    }
}

std::string Edition::SelectButton::getSelectedOption() const {
    if (selectedOption >= 0 && static_cast<size_t>(selectedOption) < options.size()) {
        return options[selectedOption];
    }
    return "";
}

void Edition::SelectButton::toggleDropdown() {
    isDropdownOpen = !isDropdownOpen;
}

void Edition::SelectButton::setPosition(sf::Vector2f pos) {
    box.setPosition(pos);
}
