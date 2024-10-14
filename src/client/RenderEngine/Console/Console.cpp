/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Console
*/

#include "Console.hpp"

RType::Console::Console()
{
    _showDeveloperConsole = false;
}

RType::Console::~Console()
{
}

void RType::Console::displayDeveloperConsole(sf::RenderWindow& window)
{
    if (_showDeveloperConsole == false) // Do not display the console if it's hidden
        return;

    // Display the console
    this->displayContainer(window);
    this->displayCloseContainerButton(window);
}

void RType::Console::toggleDeveloperConsoleFromEvent(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::T) {
            this->toggleDeveloperConsole();
        }
    }
}

void RType::Console::displayContainer(sf::RenderWindow &window)
{
    // Display the container of the console at the bottom left of the window
    unsigned int width = window.getSize().x;
    unsigned int height = window.getSize().y;

    // If width is smaller than 800 or height is smaller than 600, do not display the console
    if (width < 800 || height < 600)
        return;

    // Console width = 50% of the window width
    // Console height = 40% of the window height
    unsigned int consoleWidth = width * 0.5;
    unsigned int consoleHeight = height * 0.4;

    // Console position = bottom left of the window
    unsigned int consolePosX = 0;
    unsigned int consolePosY = height - consoleHeight;

    // Create the container
    sf::RectangleShape container(sf::Vector2f(consoleWidth, consoleHeight));
    container.setPosition(consolePosX, consolePosY);
    container.setOutlineColor(sf::Color::White);
    container.setOutlineThickness(2);
    sf::Uint8 alpha = 128; // 50% opacity
    sf::Uint8 red = 46;
    sf::Uint8 green = 46;
    sf::Uint8 blue = 46;
    container.setFillColor(sf::Color(red, green, blue, alpha));

    // Display the container
    window.draw(container);
}

void RType::Console::displayCloseContainerButton(sf::RenderWindow &window)
{
    // Display the close button at the top right of the container
    unsigned int width = window.getSize().x;
    unsigned int height = window.getSize().y;

    // If width is smaller than 800 or height is smaller than 600, do not display the console
    if (width < 800 || height < 600)
        return;

    // Console width = 50% of the window width
    // Console height = 40% of the window height
    unsigned int consoleWidth = width * 0.5;
    unsigned int consoleHeight = height * 0.4;

    // Console position = bottom left of the window
    unsigned int consolePosX = 0;
    unsigned int consolePosY = height - consoleHeight;

    // Close button size = 20x20
    unsigned int closeBtnSize = 20;

    // Close button position = top right of the container
    unsigned int closeBtnPosX = consolePosX + consoleWidth - closeBtnSize;
    unsigned int closeBtnPosY = consolePosY;

    // Create the close button
    sf::RectangleShape closeBtn(sf::Vector2f(closeBtnSize, closeBtnSize));
    closeBtn.setPosition(closeBtnPosX, closeBtnPosY);
    closeBtn.setOutlineColor(sf::Color::White);
    closeBtn.setOutlineThickness(2);
    sf::Uint8 alpha = 128; // 50% opacity

    closeBtn.setFillColor(sf::Color(255, 0, 0, alpha));

    // Display the close button
    window.draw(closeBtn);

    // Handle click on the close button
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (closeBtn.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            this->toggleDeveloperConsole();
            return;
        }
    }
}

int main() {
    // Temp main function to test the Console class
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "R-Type");
    RType::Console console;

    console.toggleDeveloperConsole();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // Recalculate display if the window is resized
            if (event.type == sf::Event::Resized) {
                // Optionally adjust the view if needed
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            console.toggleDeveloperConsoleFromEvent(event);
        }

        window.clear();
        console.displayDeveloperConsole(window);
        window.display();
    }
}