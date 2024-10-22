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


Edition::EditionScreen::EditionScreen()
{
    _centralArea.setSize(sf::Vector2f(1350, 900));
    _centralArea.setPosition(20, 100);
    _centralArea.setFillColor(sf::Color(50, 50, 50));
    _centralArea.setOutlineThickness(1);
    _centralArea.setOutlineColor(sf::Color::White);

    commandManager = CommandManager();
}

Edition::EditionScreen::~EditionScreen()
{
}

void Edition::EditionScreen::draw(sf::RenderWindow &window)
{
    window.draw(_centralArea);

    for (const auto &asset : commandManager.getUndoAssets()) {
        asset->draw(window);
    }
}

std::shared_ptr<Edition::Asset> Edition::EditionScreen::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (const auto &asset : commandManager.getUndoAssets()) {
            if (asset->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                return asset;
            }
        }
    }
    return nullptr;
}

bool Edition::EditionScreen::displaySaveDialog(std::shared_ptr<sf::RenderWindow> window)
{
    // Display a dialog to save the scene
    sf::RectangleShape dialog(sf::Vector2f(400, 200));
    dialog.setFillColor(sf::Color(50, 50, 50));
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

void Edition::EditionScreen::saveScene(const std::string &sceneName)
{
    // Add prefix and extension to the scene name
    // Fileconfig: "./config" + PATH_SEPARATOR + "scenes" + PATH_SEPARATOR + sceneName + ".cfg"
    std::string scenePath = std::string("config") + PATH_SEPARATOR + "scenes" + PATH_SEPARATOR + sceneName + ".cfg";

    // Save the scene
    // libconfig::Config cfg;
}