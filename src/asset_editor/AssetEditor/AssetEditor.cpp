/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** AssetEditor
*/

#include "AssetEditor.hpp"

Edition::AssetEditor::AssetEditor()
{
    _window.create(sf::VideoMode(1920, 1080), "Asset Editor");
    _rightSidebar = std::make_shared<RightSidebar>();
}

Edition::AssetEditor::~AssetEditor()
{
}

void Edition::AssetEditor::run()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear();
        _rightSidebar->draw(_window);
        _window.display();
    }
}