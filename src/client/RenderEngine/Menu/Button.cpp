/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color color, int outline, sf::Color outlineColor) {
    this->shape.setSize(size);
    this->shape.setOutlineThickness(outline);
    this->shape.setOutlineColor(outlineColor);
    this->shape.setPosition(pos.x, pos.y);
    this->shape.setFillColor(color);
    this->hoverSape.setSize(size);
    this->hoverSape.setPosition(pos.x, pos.y);
    this->hoverSape.setFillColor(sf::Color::Black);
    this->_characterSize = 0;
}

Button::~Button() {
}

bool Button::checkClick(std::shared_ptr<sf::RenderWindow> window, sf::Event event) {
    sf::Mouse mouse;
    sf::Vector2f mousPos  = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
    sf::Vector2f mousPos2 = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

    this->setState(StateButton::None);
    if (this->shape.getGlobalBounds().contains(mousPos2)) this->setState(StateButton::Hover);
    if (this->shape.getGlobalBounds().contains(mousPos)) {
        if (mouse.isButtonPressed(sf::Mouse::Button::Left)) {
            this->setState(StateButton::Clicked);
            return (true);
        }
    }
    return (false);
}

void Button::displayButton(std::shared_ptr<sf::RenderWindow> window) {
    std::string font_path("assets/r-type.ttf");
    sf::Font font;
    sf::Color color = this->hoverSape.getFillColor();

    if (this->state == StateButton::None) {
        color.a = 0;
        this->hoverSape.setFillColor(color);
    } else if (this->state == StateButton::Hover) {
        color.a = 30;
        this->hoverSape.setFillColor(color);
    } else {
        color.a = 50;
        this->hoverSape.setFillColor(color);
    }
    this->shape.setTexture(&this->Texture);
    window->draw(this->shape);
    if (font.loadFromFile(font_path)) {
        this->renderText.setFont(font);
        this->renderText.setString(this->text);
        this->renderText.setCharacterSize(this->_characterSize);
        this->renderText.setFillColor(sf::Color::White);
        this->renderText.setPosition(
            this->shape.getGlobalBounds().left
                + (this->shape.getGlobalBounds().width - this->renderText.getGlobalBounds().width) / 2,
            this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height / 4);
    }
    window->draw(this->renderText);
    window->draw(this->hoverSape);
}

void Button::setState(StateButton newState) {
    this->state = newState;
}

void Button::setText(std::string newText, size_t size) {
    this->text           = newText;
    this->_characterSize = size;
    this->renderText.setPosition(
        this->shape.getGlobalBounds().left
            + (this->shape.getGlobalBounds().width - this->renderText.getGlobalBounds().width) / 2,
        this->shape.getGlobalBounds().top
            + (this->shape.getGlobalBounds().height - this->renderText.getGlobalBounds().height) / 2);
}

void Button::setPosition(sf::Vector2f pos) {
    this->shape.setPosition(pos);
    this->hoverSape.setPosition(pos);
}

std::string Button::getText() const {
    return (this->text);
}

void Button::setSprite(sf::Sprite sprite) {
    this->Texture.loadFromImage(sprite.getTexture()->copyToImage());
}