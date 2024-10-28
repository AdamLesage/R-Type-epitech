/*
** EPITECH PROJECT, 2024
** R-Type-epitech [WSL: Ubuntu]
** File description:
** Toolbar
*/

#include "Toolbar.hpp"

Toolbar::Toolbar() : showFps(false), showMemory(false), showCpu(false), showGpu(false),
    showNetwork(false), showPlayerPos(false), isVisible(false), dropdownOpen(false)
{
    toolbarShape.setSize({1920, 50});
    toolbarShape.setFillColor(sf::Color(50,50,50));

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font" << std::endl;
    }

    text.setFont(font);
    text.setString("Overlay");
    text.setPosition(10, 5);
    dropdownShape.setSize({150, 180});
    dropdownShape.setFillColor(sf::Color(70, 70, 70));
    dropdownShape.setPosition(10, 50);
    initializeMenuOptions();
}

Toolbar::~Toolbar()
{
}

void Toolbar::initializeMenuOptions()
{
    optionSelected = {{"FPS", false}, {"CPU Usage", false}, {"GPU Usage", false},
        {"RAM", false}, {"World Position", false}, {"Network", false}};
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
    sf::Text networkOption("Network", font, 25);
    networkOption.setFillColor(sf::Color::White);
    networkOption.setPosition(20, 200);

    menuOptions["FPS"] = fpsOption;
    menuOptions["CPU Usage"] = cpuOption;
    menuOptions["GPU Usage"] = gpuOption;
    menuOptions["RAM"] = ramOption;
    menuOptions["World position"] = posOption;
    menuOptions["Network"] = networkOption;
}

void Toolbar::open()
{
    isVisible = !isVisible;
}

void Toolbar::updateHoveredOption(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    hoveredOpt.clear();
    for (auto& [optionName, textOption] : menuOptions) {
        if (textOption.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            hoveredOpt = optionName;
        }
    }
}

void Toolbar::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3) {
        if (dropdownOpen) {
            dropdownOpen = false;
            hoveredOpt.clear();
        } else {
            dropdownOpen = true;
            dropdownOpen = false;
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        updateHoveredOption(window);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (text.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            dropdownOpen = !dropdownOpen;
            if (dropdownOpen) {
                hoveredOpt.clear();
            } else {
                dropdownOpen = false;
            }
        }
        if (dropdownOpen) {
            for (auto& [optionName, optionText] : menuOptions) {
                if (optionText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    optionSelected[optionName] = !optionSelected[optionName];
                    std::cout << optionName << ":" << (optionSelected[optionName] ? "ON" : "OFF") << std::endl;
                    displayMetrics(optionName);
                }
            }
        }
    }
}

void Toolbar::displayMetrics(const std::string optionName)
{
    if (optionName == "FPS") {
        showFps = optionSelected[optionName];
    }
    if (optionName == "RAM") {
        showMemory = optionSelected[optionName];
    }
    if (optionName == "CPU Usage") {
        showCpu = optionSelected[optionName];
    }
    if (optionName == "GPU Usage") {
        showGpu = optionSelected[optionName];
    }
    if (optionName == "Network") {
        showNetwork = optionSelected[optionName];
    }
    if (optionName == "World position") {
        showPlayerPos = optionSelected[optionName];
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
        for (auto& [name, textOption] : menuOptions) {
            if (name == hoveredOpt) {
                textOption.setFillColor(sf::Color::Yellow);
            } else {
                textOption.setFillColor(sf::Color::White);
            }
            window.draw(textOption);
        }
    }
}