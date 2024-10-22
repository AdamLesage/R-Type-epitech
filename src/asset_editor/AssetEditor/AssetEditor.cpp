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
    _window->create(sf::VideoMode(1920, 1080), "Asset Editor", sf::Style::Titlebar | sf::Style::Close);
    _rightSidebar = std::make_shared<RightSidebar>();
    _toolbar = Toolbar();
    _editionScreen = EditionScreen();
    _lastEntityCode = 50; // Starting to 50 to avoid used code in PROTOCOL.md
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
            this->handleToolbarEvents(event);
            std::shared_ptr<Edition::Asset> asset = this->_editionScreen.handleEvent(event);
            if (asset != nullptr) {
                _rightSidebar->updateSelectedEntity(asset);
            }
        }
        _window->clear();
        _toolbar.draw(*_window.get());
        _editionScreen.draw(*_window.get());
        displayToolbarEvents();
        if (mouseTexture != nullptr) {
            _window->draw(*mousePickRect.get());
        }
        _rightSidebar->draw(_window);
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
        if (mousePickRect != nullptr && !mousePathTexture.empty() && _lastEntityCode < 100) { // Limit the number of entities to 100
            std::shared_ptr<Edition::Asset> asset = std::make_shared<Edition::Asset>(event.mouseButton.x, event.mouseButton.y, mousePathTexture, _lastEntityCode);
            _lastEntityCode++; // Increment the entity code
            this->_editionScreen.commandManager.createAsset(asset);
        }

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

void Edition::AssetEditor::handleToolbarEvents(const sf::Event &event)
{
    // Handle undo and redo from keyboard input
    if (event.type == sf::Event::KeyPressed) {
        if ((event.key.code == sf::Keyboard::Z) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
            this->_toolbar.setCurrentSelection(CurrentSelection::UNDO);
        }
        if ((event.key.code == sf::Keyboard::Y) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
            this->_toolbar.setCurrentSelection(CurrentSelection::REDO);
        }
    }

    if (this->_toolbar.getCurrentSelection() == CurrentSelection::MOVE) // Client can move on the edition screen without any asset selected
        return;

    if (this->_toolbar.getCurrentSelection() == CurrentSelection::UNDO) {
        this->_toolbar.setCurrentSelection(CurrentSelection::MOVE);
        this->_editionScreen.commandManager.undo();
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::REDO) {
        this->_editionScreen.commandManager.redo();
        this->_toolbar.setCurrentSelection(CurrentSelection::MOVE);
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::SAVE) {
        this->_editionScreen.retrieveInputSaveScene(event);
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::LOAD) {
        // this->_editionScreen.load();
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::DELETE) {
        // this->_editionScreen.deleteEditionScreen();
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::ZOOM) {
        // this->_editionScreen.zoomOnEditionScreen();
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::DEZOOM) {
        // this->_editionScreen.dezoomOnEditionScreen();
    }
}

void Edition::AssetEditor::displayToolbarEvents()
{
    if (this->_toolbar.getCurrentSelection() == CurrentSelection::MOVE) {
        return; // Display the move cursor
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::UNDO) {
        // Display the undo cursor
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::REDO) {
        // Display the redo cursor
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::SAVE) {
        bool playerActionOnWindow = this->_editionScreen.displaySaveDialog(_window);
        if (playerActionOnWindow == false) {
            this->_toolbar.setCurrentSelection(CurrentSelection::MOVE);
        }
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::LOAD) {
        // Display the load cursor
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::DELETE) {
        // Display the delete cursor
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::ZOOM) {
        // Display the zoom cursor
    } else if (this->_toolbar.getCurrentSelection() == CurrentSelection::DEZOOM) {
        // Display the dezoom cursor
    }
}