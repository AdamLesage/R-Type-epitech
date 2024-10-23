/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** EditionScreen
*/

#include "EditionScreen.hpp"


#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define LIB_EXTENSION ".dll"
    #define PATH_SEPARATOR "\\"
#else
    #include <dlfcn.h>
    #define LIB_EXTENSION ".so"
    #define PATH_SEPARATOR "/"
#endif


Edition::EditionScreen::EditionScreen() : _zoomFactor(1.0f), _centralAreaPosition(0, 100), _centralAreaSize(1900, 900)
{
    _centralArea.setSize(sf::Vector2f(_centralAreaSize.x, _centralAreaSize.y));
    _centralArea.setPosition(_centralAreaPosition.x, _centralAreaPosition.y);
    _centralArea.setFillColor(sf::Color(50, 50, 50));
    _centralArea.setOutlineThickness(1);
    _centralArea.setOutlineColor(sf::Color::White);

    _centralView.setSize(1350, 900);
    _centralView.setCenter(_centralAreaPosition.x + _centralAreaSize.x / 2, 
                           _centralAreaPosition.y + _centralAreaSize.y / 2);

    commandManager = CommandManager();
}

Edition::EditionScreen::~EditionScreen()
{
}

void Edition::EditionScreen::draw(sf::RenderWindow &window)
{
    window.draw(_centralArea);
    window.setView(_centralView);
    for (const auto &asset : commandManager.getUndoAssets()) {
        auto bounds = asset->getGlobalBounds();
        asset->draw(window);
    }
    window.setView(window.getDefaultView());
}

std::shared_ptr<Edition::Asset> Edition::EditionScreen::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window), _centralView);

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousPos;
        mousPos.x = static_cast<float>(event.mouseMove.x);
        mousPos.y = static_cast<float>(event.mouseMove.y);
        sf::FloatRect area(200.0f, 200.0f, 1300.0f, 1080.0f);
        if (area.contains(mousPos)) {
            _isInArea = true;
        } else {
            _isInArea = false;
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && _isInArea) {
        sf::Vector2f mousPos;
        mousPos.x = static_cast<float>(event.mouseButton.x);
        mousPos.y = static_cast<float>(event.mouseButton.y);
        for (const auto &asset : commandManager.getUndoAssets()) {
            if (asset->getGlobalBounds().contains(mouseWorldPos.x, mouseWorldPos.y)) {
                return asset;
            }
        }
    }
    if (event.type == sf::Event::MouseWheelScrolled && _isInArea) {
        if (event.mouseWheelScroll.delta > 0) {
            _centralView.zoom(0.9f);
            _zoomFactor *= 0.9f;
        } else if (event.mouseWheelScroll.delta < 0) {
            if (_zoomFactor < 1) {
                _centralView.zoom(1.1f);
                _zoomFactor *= 1.1f;
            }
        }
    }

    if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left) && _isInArea) {
        static sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);
        sf::Vector2i newMousePos = sf::Mouse::getPosition(window);
        sf::Vector2f delta(static_cast<float>(lastMousePos.x - newMousePos.x), 
                           static_cast<float>(0));
        
        delta.x = std::clamp(delta.x, -15.0f * _zoomFactor, 15.0f * _zoomFactor);
        sf::Vector2f viewCenter = _centralView.getCenter();
        sf::Vector2f viewSize = _centralView.getSize();
        _viewLeftEdge = viewCenter.x - viewSize.x / 2.0f;

        if (_viewLeftEdge + delta.x >= 20) {
            _centralView.move(delta);
        }

        lastMousePos = newMousePos;
    }

    return nullptr;
}

bool Edition::EditionScreen::displaySaveDialog(std::shared_ptr<sf::RenderWindow> window)
{
    // Display a dialog to save the scene
    sf::RectangleShape dialog(sf::Vector2f(400, 200));
    dialog.setFillColor(sf::Color(75, 75, 75));
    dialog.setOutlineThickness(1);
    dialog.setOutlineColor(sf::Color::White);
    dialog.setPosition(window->getSize().x / 2 - dialog.getSize().x / 2, window->getSize().y / 2 - dialog.getSize().y / 2);

    // Display button on the top right to close the dialog
    sf::RectangleShape closeButton(sf::Vector2f(20, 20));
    closeButton.setFillColor(sf::Color::Red);
    closeButton.setPosition(dialog.getPosition().x + dialog.getSize().x - closeButton.getSize().x, dialog.getPosition().y);

    // If the close button is clicked, close the dialog
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window.get());
        if (closeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Close the dialog" << std::endl;
            _inputSaveText.setString("");
            return false;
        }
    }

    // Display text to save the scene
    sf::Font font;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    font.loadFromFile(fontPath);
    sf::Text text;
    text.setFont(font);
    text.setString("Save the scene ?");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(dialog.getPosition().x + dialog.getSize().x / 2 - text.getGlobalBounds().width / 2, dialog.getPosition().y + 20);

    // Display input field to enter the name of the scene
    sf::RectangleShape inputField(sf::Vector2f(200, 30));
    inputField.setFillColor(sf::Color::White);
    inputField.setPosition(dialog.getPosition().x + dialog.getSize().x / 2 - inputField.getSize().x / 2, dialog.getPosition().y + 100);

    // Display the text of the input field
    _inputSaveText.setFont(font);
    _inputSaveText.setCharacterSize(20);
    _inputSaveText.setFillColor(sf::Color::Black);
    _inputSaveText.setPosition(inputField.getPosition().x + 10, inputField.getPosition().y + 5);

    // Display the button to save the scene
    sf::RectangleShape saveButton(sf::Vector2f(100, 30));
    saveButton.setFillColor(sf::Color::Green);
    saveButton.setPosition(dialog.getPosition().x + dialog.getSize().x / 2 - saveButton.getSize().x / 2, dialog.getPosition().y + 150);
    saveButton.setOutlineThickness(1);
    saveButton.setOutlineColor(sf::Color::White);

    // Display the text of the save button
    sf::Text saveText;
    saveText.setFont(font);
    saveText.setString("Save");
    saveText.setCharacterSize(20);
    saveText.setFillColor(sf::Color::White);
    saveText.setPosition(saveButton.getPosition().x + saveButton.getSize().x / 2 - saveText.getGlobalBounds().width / 2, saveButton.getPosition().y + 5);

    // If the save button is clicked, save the scene
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window.get());
        if (saveButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            // Save the scene
            this->saveScene(_inputSaveText.getString());
            _inputSaveText.setString("");
            return false;
        }
    }

    // Display the dialog
    window->draw(dialog);
    window->draw(closeButton);
    window->draw(text);
    window->draw(inputField);
    window->draw(_inputSaveText);
    window->draw(saveButton);
    window->draw(saveText);

    return true;
}

void Edition::EditionScreen::retrieveInputSaveScene(const sf::Event &event)
{
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !_inputSaveText.getString().isEmpty()) { // Handle backspace
            std::string sceneName = _inputSaveText.getString();
            sceneName.pop_back();
            _inputSaveText.setString(sceneName);
        } else if (event.text.unicode < 128 && event.text.unicode > 31) { // Handle printable characters
            std::string sceneName = _inputSaveText.getString();
            sceneName += static_cast<char>(event.text.unicode);
            _inputSaveText.setString(sceneName);
        }
    }
}

bool Edition::EditionScreen::displayDeleteDialog(std::shared_ptr<sf::RenderWindow> window)
{
    // Display a dialog to delete the scene
    sf::RectangleShape dialog(sf::Vector2f(600, 200));
    dialog.setFillColor(sf::Color(75, 75, 75));
    dialog.setOutlineThickness(1);
    dialog.setOutlineColor(sf::Color::White);
    dialog.setPosition(window->getSize().x / 2 - dialog.getSize().x / 2, window->getSize().y / 2 - dialog.getSize().y / 2);

    // Display button on the top right to close the dialog
    sf::RectangleShape closeButton(sf::Vector2f(20, 20));
    closeButton.setFillColor(sf::Color::Red);
    closeButton.setPosition(dialog.getPosition().x + dialog.getSize().x - closeButton.getSize().x, dialog.getPosition().y);

    // If the close button is clicked, close the dialog
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window.get());
        if (closeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Close the dialog" << std::endl;
            return false;
        }
    }

    // Display text to delete the scene
    sf::Font font;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    font.loadFromFile(fontPath);
    sf::Text text;
    text.setFont(font);
    text.setString("Are you sure you want to delete the scene ?\n(No way to undo)");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(dialog.getPosition().x + dialog.getSize().x / 2 - text.getGlobalBounds().width / 2, dialog.getPosition().y + 20);

    // Display the button to delete the scene
    sf::RectangleShape deleteButton(sf::Vector2f(100, 30));
    deleteButton.setFillColor(sf::Color::Red);
    deleteButton.setPosition(dialog.getPosition().x + dialog.getSize().x / 2 - deleteButton.getSize().x / 2, dialog.getPosition().y + 150);
    deleteButton.setOutlineThickness(1);
    deleteButton.setOutlineColor(sf::Color::White);

    // Display the text of the delete button
    sf::Text deleteText;
    deleteText.setFont(font);
    deleteText.setString("Delete");
    deleteText.setCharacterSize(20);
    deleteText.setFillColor(sf::Color::White);
    deleteText.setPosition(deleteButton.getPosition().x + deleteButton.getSize().x / 2 - deleteText.getGlobalBounds().width / 2, deleteButton.getPosition().y + 5);

    // If the delete button is clicked, delete the scene
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window.get());
        if (deleteButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            // Delete the scene
            this->deleteEditionScreen();
            return false;
        }
    }

    // Display the dialog
    window->draw(dialog);
    window->draw(closeButton);
    window->draw(text);
    window->draw(deleteButton);
    window->draw(deleteText);

    return true;
}

void Edition::EditionScreen::saveScene(const std::string &sceneName)
{
    // Add prefix and extension to the scene name
    // Fileconfig: "./config" + PATH_SEPARATOR + "scenes" + PATH_SEPARATOR + sceneName + ".cfg"
    std::string scenePath = std::string("config") + PATH_SEPARATOR + "scenes" + PATH_SEPARATOR + sceneName + ".cfg";
    SaveScene saveScene = SaveScene(scenePath, commandManager.getUndoAssets());

    saveScene.save();
}

void Edition::EditionScreen::deleteEditionScreen()
{
    commandManager.clearRedoAssets();
    commandManager.clearUndoAssets();
}

float Edition::EditionScreen::getViewLeftEdge()
{

    return this->_viewLeftEdge;
}

sf::View Edition::EditionScreen::getView()
{
    return this->_centralView;
}
