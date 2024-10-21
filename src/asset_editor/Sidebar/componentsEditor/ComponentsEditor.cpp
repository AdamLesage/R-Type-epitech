/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ComponentsEditor
*/

#include "ComponentsEditor.hpp"

Edition::ComponentsEditor::ComponentsEditor()
{
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    label.reset(new Input(sf::Vector2f(350, 40), sf::Vector2f(1460, 80), "Label: "));
    posX.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1460, 200), "X: "));
    posY.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1460 + 115, 200), "Y: "));
    sizeX.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1460, 250 + 50), "X: "));
    sizeY.reset(new InputNumber(sf::Vector2f(70, 40), sf::Vector2f(1460 + 115,  250 + 50), "Y: "));
    rotation.reset(new InputNumber(sf::Vector2f(70,40), sf::Vector2f(1460, 350), "Rotation: "));
}

Edition::ComponentsEditor::~ComponentsEditor()
{
}

void Edition::ComponentsEditor::displayCategoryTitle(std::shared_ptr<sf::RenderWindow> window, std::string title, float posX, float posY)
{
    sf::Text text;
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(static_cast<float>(posX), static_cast<float>(posY));

    window->draw(text);
}


void Edition::ComponentsEditor::display(std::shared_ptr<sf::RenderWindow> window)
{
    label->displayInput(window);
    displayCategoryTitle(window, "Position", window->getSize().x * 0.76, 150);
    posX->displayInput(window);
    posY->displayInput(window);
    displayCategoryTitle(window, "Size", window->getSize().x * 0.76, 250);
    sizeX->displayInput(window);
    sizeY->displayInput(window);
    rotation->displayInput(window);
}

void Edition::ComponentsEditor::updateSelectedEntity(std::shared_ptr<Edition::Asset> asset)
{
    _asset = asset;
    this->posX->setInput(std::to_string(static_cast<int>(_asset->getGlobalBounds().left)));
    this->posY->setInput(std::to_string(static_cast<int>(_asset->getGlobalBounds().top)));
    this->sizeX->setInput(std::to_string(static_cast<int>(_asset->getGlobalBounds().width)));
    this->sizeY->setInput(std::to_string(static_cast<int>(_asset->getGlobalBounds().height)));
}

void Edition::ComponentsEditor::handleInput(const sf::Event &event)
{
    if (event.type == sf::Event::TextEntered || event.type == sf::Event::MouseButtonPressed) {
        label->checkInput(event);
        if (posX->checkInput(event) && this->_asset != nullptr) {
            if (posX->getInput().empty()) {
                this->_asset->move(0, _asset->getGlobalBounds().top);
            } else {
                this->_asset->move(std::stoi(posX->getInput()), _asset->getGlobalBounds().top);
            }
        }
        if (posY->checkInput(event) && this->_asset != nullptr) {
            if (posY->getInput().empty()) {
                this->_asset->move(_asset->getGlobalBounds().left, 0);
            } else {
                this->_asset->move(_asset->getGlobalBounds().left, std::stoi(posY->getInput()));
            }
        }
        rotation->checkInput(event);
        sizeX->checkInput(event);
        sizeY->checkInput(event);
    }
}