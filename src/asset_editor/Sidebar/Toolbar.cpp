/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Toolbar
*/

#include "Toolbar.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define LIB_EXTENSION ".dll"
    #define PATH_SEPARATOR "\\"
#else
    #include <dlfcn.h>
    #define LIB_EXTENSION ".so"
    #define PATH_SEPARATOR "/"
#endif

Edition::Toolbar::Toolbar()
{
    std::string undoPath = "assets" + std::string(PATH_SEPARATOR) + "asset_editor" + std::string(PATH_SEPARATOR) + "undo.png";
    std::string redoPath = "assets" + std::string(PATH_SEPARATOR) + "asset_editor" + std::string(PATH_SEPARATOR) + "redo.png";
    std::string savePath = "assets" + std::string(PATH_SEPARATOR) + "asset_editor" + std::string(PATH_SEPARATOR) + "save.png";
    std::string deletePath = "assets" + std::string(PATH_SEPARATOR) + "asset_editor" + std::string(PATH_SEPARATOR) + "delete.png";
    std::string movePath = "assets" + std::string(PATH_SEPARATOR) + "asset_editor" + std::string(PATH_SEPARATOR) + "move.png";
    std::string zoomPath = "assets" + std::string(PATH_SEPARATOR) + "asset_editor" + std::string(PATH_SEPARATOR) + "zoom.png";
    std::string dezoomPath = "assets" + std::string(PATH_SEPARATOR) + "asset_editor" + std::string(PATH_SEPARATOR) + "dezoom.png";

    _toolbarButtons.push_back(ToolbarButton(undoPath, sf::Vector2f(20, 5)));
    _toolbarButtons.push_back(ToolbarButton(redoPath, sf::Vector2f(70, 5)));
    _toolbarButtons.push_back(ToolbarButton(savePath, sf::Vector2f(120, 5)));
    _toolbarButtons.push_back(ToolbarButton(deletePath, sf::Vector2f(170, 5)));
    _toolbarButtons.push_back(ToolbarButton(movePath, sf::Vector2f(220, 5)));
    _toolbarButtons.push_back(ToolbarButton(zoomPath, sf::Vector2f(270, 5)));
    _toolbarButtons.push_back(ToolbarButton(dezoomPath, sf::Vector2f(320, 5)));
}


Edition::Toolbar::~Toolbar()
{
}

void Edition::Toolbar::displayToolbarButtons(sf::RenderWindow &window)
{
    for (auto &button : _toolbarButtons) {
        button.draw(window);
    }
}

void Edition::Toolbar::displayToolbarContainer(sf::RenderWindow &window)
{
    static float currentWidth = window.getSize().x;
    float targetWidth = window.getSize().x;
    float transitionSpeed = 10.0f; // Adjust this value for faster/slower transition

    if (currentWidth != targetWidth) {
        if (currentWidth < targetWidth) {
            currentWidth += transitionSpeed;
            if (currentWidth > targetWidth) currentWidth = targetWidth;
        } else {
            currentWidth -= transitionSpeed;
            if (currentWidth < targetWidth) currentWidth = targetWidth;
        }
    }

    unsigned int toolbarHeight = 50;

    sf::RectangleShape toolbar(sf::Vector2f(currentWidth, toolbarHeight));
    toolbar.setFillColor(sf::Color(50, 50, 50));
    toolbar.setPosition(0, 0);

    // Set border
    toolbar.setOutlineThickness(1);
    toolbar.setOutlineColor(sf::Color::White);

    window.draw(toolbar);
}

void Edition::Toolbar::draw(sf::RenderWindow &window)
{
    this->displayToolbarContainer(window);
    this->displayToolbarButtons(window);
}
