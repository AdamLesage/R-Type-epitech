/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetEditor
*/

#include "AssetEditor.hpp"

Edition::AssetEditor::AssetEditor()
{
    _window = std::make_shared<sf::RenderWindow>();
    _window->create(sf::VideoMode(1920, 1080), "Asset Editor");
}

Edition::AssetEditor::~AssetEditor()
{
}

void Edition::AssetEditor::run()
{
    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            this->assetSelector.handleEvent(event);
            if (event.type == sf::Event::Closed)
                _window->close();
        }
        _window->clear();
        assetSelector.display(_window);
        _window->display();
    }
}