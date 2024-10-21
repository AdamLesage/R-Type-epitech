/*
** EPITECH PROJECT, 2024
** B-OOP-400-NAN-4-1-Edition-adam.lesage
** File description:
** InputNumber
*/

#include "InputNumber.hpp"

Edition::InputNumber::InputNumber(sf::Vector2f size, sf::Vector2f pos, std::string title) : Input(size,pos, title)
{
    this->_input = "";
    this->_inputText.setFont(this->_font);
    this->_inputText.setString(this->_input);
    this->_inputText.setCharacterSize(30);
    this->_inputText.setFillColor(sf::Color::White);
    this->_inputText.setPosition(sf::Vector2f(this->_pos.x, this->_pos.y));
}

Edition::InputNumber::~InputNumber()
{
}

bool Edition::InputNumber::checkInput(const sf::Event &event)
{
    checkClick(event);
    if (this->_typing == true) {
        if (event.type == sf::Event::TextEntered) {
            if (static_cast<char>(event.text.unicode) == 8) {
                if (this->_input.size() != 0) {
                    this->_input.pop_back();
                    this->updateText();
                    return true;
                }
            } else if (static_cast<char>(event.text.unicode) >= '0' && static_cast<char>(event.text.unicode) <= '9'){
                this->_input.push_back(static_cast<char>(event.text.unicode));
                this->updateText(); 
                return true;
            }
        }
    }
    return false;
}