/*
** EPITECH PROJECT, 2024
** rtype [WSL: Ubuntu-22.04]
** File description:
** Toolbar
*/

#include "Toolbar.hpp"

Toolbar::Toolbar() : isVisible(false), dropdownOpen(false)
{
    toolbarShape.setSize({1920, 50});
    toolbarShape.setFillColor(sf::Color(50,50,50));

    if (!font.loadFromFile("./assets/r-type.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    text.setFont(font);
    text.setString("Overlay");
    text.setPosition(10, 5);
    dropdownShape.setSize({150, 150});
    dropdownShape.setFillColor(sf::Color(70, 70, 70));
    dropdownShape.setPosition(10, 50);
    initializeMenuOptions();
}

Toolbar::~Toolbar()
{
}

void Toolbar::initializeMenuOptions()
{
    optionSelected = {{"FPS", false}, {"CPU Usage", false}, {"GPU Usage", false}, {"RAM", false}, {"World Position", false}};
    sf::Text fpsOption("FPS", font, 25);
    fpsOption.setFillColor(sf::Color::White);
    fpsOption.setPosition(20, 50);
    sf::Text cpuOption("CPU Usage", font, 25);
    cpuOption.setFillColor(sf::Color::White);
    cpuOption.setPosition(20, 80);
    sf::Text gpuOption("GPU Usage", font, 25);
    gpuOption.setFillColor(sf::Color::White);
    gpuOption.setPosition(20, 110);
    sf::Text ramOption("RAM", font, 25);
    ramOption.setFillColor(sf::Color::White);
    ramOption.setPosition(20, 140);
    sf::Text posOption("World Position", font, 25);
    posOption.setFillColor(sf::Color::White);
    posOption.setPosition(20, 170);
    menuOptions["FPS"] = fpsOption;
    menuOptions["CPU Usage"] = cpuOption;
    menuOptions["GPU Usage"] = gpuOption;
    menuOptions["RAM"] = ramOption;
    menuOptions["World position"] = posOption;
}

void Toolbar::open()
{
    isVisible = !isVisible;
}

void Toolbar::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (text.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            dropdownOpen = !dropdownOpen;
        }
        if (dropdownOpen) {
            for (auto& [optionName, optionText] : menuOptions) {
                if (optionText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    optionSelected[optionName] = !optionSelected[optionName];
                    std::cout << optionName << ":" << (optionSelected[optionName] ? "ON" : "OFF") << std::endl;
                }
            }
        }
    }
}

void Toolbar::draw(sf::RenderWindow& window)
{
    if (isVisible) {
        window.draw(toolbarShape);
        window.draw(text);
    }
    if (dropdownOpen) {
        window.draw(dropdownShape);
        for (const auto& [name, textoption] : menuOptions) {
            window.draw(textoption);
        }
    }
}
