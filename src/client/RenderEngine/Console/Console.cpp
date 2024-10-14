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

void RType::Console::displayDeveloperConsole(sf::RenderWindow &window)
{
    if (_showDeveloperConsole == false) // Do not display the console if it's hidden
        return;

    // Display the console
    this->displayContainer(window);
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


// To compile this snippet, you can use the following command:
// g++ -o test Console.cpp -lsfml-graphics -lsfml-window -lsfml-system
int main()
{
    // Temp main function to test the Console class
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "R-Type");
    RType::Console console;

    console.toggleDeveloperConsole();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Red); // Set the background color to red
        console.displayDeveloperConsole(window);
        window.display();
    }
}