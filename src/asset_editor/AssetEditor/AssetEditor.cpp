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
    _rightSidebar = std::make_shared<RightSidebar>();
    _toolbar = Toolbar();
    _editionScreen = EditionScreen();
}

Edition::AssetEditor::~AssetEditor()
{
}

void Edition::AssetEditor::run()
{
    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            std::string texture = this->_rightSidebar->handleEvent(event);
            manageDragAndDrop(event, texture);
            std::shared_ptr<Edition::Asset> asset = this->_editionScreen.handleEvent(event);
            if (asset != nullptr) {
                _rightSidebar->updateSelectedEntity(asset);
            }
        }
        _window->clear();
        _toolbar.draw(*_window.get());
        _rightSidebar->draw(_window);
        _editionScreen.draw(*_window.get());
        if (mouseTexture != nullptr) {
            _window->draw(*mousePickRect.get());
        }
        _window->display();
    }
}

void Edition::AssetEditor::manageDragAndDrop(sf::Event &event, std::string &texturPath)
{
    if (!texturPath.empty() && !mouseTexture) {
        mousePickRect = std::make_unique<sf::RectangleShape>(sf::Vector2f(_window->getSize().x * 0.20f, 100.f));
        mousePathTexture = texturPath;

        mouseTexture = std::make_unique<sf::Texture>();
        if (!mouseTexture->loadFromFile(mousePathTexture)) {
            std::cerr << "Failed to load texture from " << mousePathTexture << std::endl;
            mouseTexture.reset();
        } else {
            mousePickRect->setTexture(mouseTexture.get());
        }
        mousePickRect->setPosition(
            event.mouseButton.x - mousePickRect->getSize().x / 2,
            event.mouseButton.y - mousePickRect->getSize().y / 2
        );
    }
    if (event.type == sf::Event::Closed) {
        _window->close();
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        mousePathTexture.clear();
        mouseTexture.reset();
    }
    if (event.type == sf::Event::MouseMoved) {
        if (mousePickRect) {
            mousePickRect->setPosition(
                event.mouseMove.x - mousePickRect->getSize().x / 2,
                event.mouseMove.y - mousePickRect->getSize().y / 2
            );
        }
    }
}
