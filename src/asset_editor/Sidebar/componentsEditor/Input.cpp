/*
** EPITECH PROJECT, 2024
** B-OOP-400-NAN-4-1-Edition-adam.lesage
** File description:
** Input
*/

#include "Input.hpp"

Edition::Input::Input(sf::Vector2f size, sf::Vector2f pos, std::string title) {
    this->_size      = size;
    this->_pos       = pos;
    this->fontLoaded = false;
    this->_back.reset(new sf::RectangleShape(size));
    this->_back->setFillColor(sf::Color(30, 30, 30));
    this->_back->setOutlineColor(sf::Color::Black);
    this->_back->setOutlineThickness(1);
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (this->_font.loadFromFile(fontPath)) {
        this->fontLoaded = true;
    }
    this->_titleText.setFont(this->_font);
    this->_titleText.setString(title);
    this->_titleText.setCharacterSize(35);
    this->_titleText.setFillColor(sf::Color::White);
    this->_titleText.setPosition(sf::Vector2f(this->_pos.x, this->_pos.y));
    this->_typing = false;
    if (!title.empty()) {
        this->_pos.x += this->_titleText.getLocalBounds().width;
    }
    this->_back->setPosition(this->_pos);
}

Edition::Input::~Input() {
}

void Edition::Input::checkClick(const sf::Event& event) {
    sf::Vector2f mousPos;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
        mousPos.x = static_cast<float>(event.mouseButton.x);
        mousPos.y = static_cast<float>(event.mouseButton.y);
        if (this->_back->getGlobalBounds().contains(mousPos)) {
            this->_typing = true;
            this->_back->setFillColor(sf::Color(20, 20, 20));
        } else {
            this->_back->setFillColor(sf::Color(30, 30, 30));
            this->_typing = false;
        }
    }
}

bool Edition::Input::checkInput(const sf::Event& event) {
    checkClick(event);
    if (this->_typing) {
        if (event.type == sf::Event::TextEntered) {
            if (static_cast<char>(event.text.unicode) == 8) {
                if (!this->_input.empty()) {
                    this->_input.pop_back();
                    this->updateText();
                    return true;
                }
            } else {
                this->_input.push_back(static_cast<char>(event.text.unicode));
                this->updateText();
                return true;
            }
        }
    }
    return false;
}

void Edition::Input::displayInput(std::shared_ptr<sf::RenderWindow> window) {
    window->draw(*this->_back.get());
    window->draw(this->_inputText);
    window->draw(this->_titleText);
}

void Edition::Input::updateText() {
    this->_inputText.setFont(this->_font);
    this->_inputText.setString(this->_input);
    this->_inputText.setCharacterSize(30);
    this->_inputText.setFillColor(sf::Color::White);
    const sf::FloatRect textBounds = this->_inputText.getLocalBounds();
    const sf::Vector2f boxSize     = _back->getSize();
    this->_inputText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                               textBounds.top + textBounds.height / 2.0f);
    this->_inputText.setPosition(this->_back->getPosition().x + boxSize.x / 2.0f,
                                 this->_back->getPosition().y + boxSize.y / 2.0f);
}

std::string Edition::Input::getInput() const {
    return this->_input;
}

void Edition::Input::setInput(std::string input) {
    this->_input = input;
    this->updateText();
}

void Edition::Input::setPosition(sf::Vector2f pos) {
    this->_pos = pos;
    this->_titleText.setPosition(sf::Vector2f(this->_pos.x, this->_pos.y));
    if (!this->_titleText.getString().isEmpty()) {
        this->_pos.x += this->_titleText.getLocalBounds().width;
    }
    this->_back->setPosition(this->_pos);
    updateText();
}