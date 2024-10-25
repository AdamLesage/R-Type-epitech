/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** server
*/

#include "network/Server.hpp"
#include <thread>
#include "GameLogique/GameLogique.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define LIB_EXTENSION ".dll"
#define PATH_SEPARATOR "\\"
#else
#include <dlfcn.h>
#define LIB_EXTENSION ".so"
#define PATH_SEPARATOR "/"
#endif

void getUserInput(int& port, int& frequency)
{
    sf::RenderWindow window(sf::VideoMode(400, 350), "Input Port and Framerate");

    sf::Font font;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font\n";
        return;
    }

    // Text labels for the fields
    sf::Text portLabel("Enter Port:", font, 20);
    portLabel.setPosition(50, 50);
    portLabel.setFillColor(sf::Color::White);

    sf::Text frequencyLabel("Enter Frequency:", font, 20);
    frequencyLabel.setPosition(50, 150);
    frequencyLabel.setFillColor(sf::Color::White);

    // Instruction message to guide the user
    sf::Text instructionText("Enter Port and press Enter", font, 18);
    instructionText.setPosition(50, 250);
    instructionText.setFillColor(sf::Color::Cyan);

    // New labels for valid number information
    sf::Text portHintText("Valid number (e.g., 5000)", font, 14);
    portHintText.setPosition(200, 90);
    portHintText.setFillColor(sf::Color::Yellow);

    sf::Text frequencyHintText("Valid number (e.g., 60)", font, 14);
    frequencyHintText.setPosition(200, 190);
    frequencyHintText.setFillColor(sf::Color::Yellow);

    // Input strings
    std::string portStr;
    std::string freqStr;

    // Display current input
    sf::Text portInput("", font, 20);
    portInput.setPosition(200, 50);
    portInput.setFillColor(sf::Color::White);

    sf::Text freqInput("", font, 20);
    freqInput.setPosition(200, 150);
    freqInput.setFillColor(sf::Color::White);

    // Rectangles for input fields
    sf::RectangleShape portBox(sf::Vector2f(150, 40));
    portBox.setPosition(190, 45);
    portBox.setFillColor(sf::Color::Black);
    portBox.setOutlineThickness(2);
    portBox.setOutlineColor(sf::Color::White);

    sf::RectangleShape freqBox(sf::Vector2f(150, 40));
    freqBox.setPosition(190, 145);
    freqBox.setFillColor(sf::Color::Black);
    freqBox.setOutlineThickness(2);
    freqBox.setOutlineColor(sf::Color::White);

    bool enterPressed     = false;
    bool portSelected     = true; // Start with the port field selected

    while (window.isOpen() && !enterPressed) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0); // Terminate the program if the window is closed
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the user clicked on the port input box
                if (portBox.getGlobalBounds().contains(
                        window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    portSelected = true;
                    portBox.setOutlineColor(sf::Color::Green); // Highlight selected box
                    freqBox.setOutlineColor(sf::Color::White);
                }
                // Check if the user clicked on the frequency input box
                if (freqBox.getGlobalBounds().contains(
                        window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    portSelected = false;
                    freqBox.setOutlineColor(sf::Color::Green); // Highlight selected box
                    portBox.setOutlineColor(sf::Color::White);
                }
            }

            if (event.type == sf::Event::TextEntered) {
                // Handle text input based on the currently selected field
                if (event.text.unicode == '\b') { // Handle backspace
                    if (portSelected && !portStr.empty())
                        portStr.pop_back();
                    else if (!portSelected && !freqStr.empty())
                        freqStr.pop_back();
                } else if (event.text.unicode == '\r') { // Handle Enter key
                    if (portSelected && !portStr.empty()) {
                        portSelected = false; // Move to the frequency field
                        instructionText.setString("Enter Frequency and press Enter");
                        freqBox.setOutlineColor(sf::Color::Green);
                        portBox.setOutlineColor(sf::Color::White);
                    } else if (!portSelected && !freqStr.empty()) {
                        instructionText.setString("Starting game...");
                        enterPressed = true; // Both fields are entered
                    }
                } else if (isdigit(event.text.unicode)) {
                    if (portSelected)
                        portStr += static_cast<char>(event.text.unicode);
                    else
                        freqStr += static_cast<char>(event.text.unicode);
                }
            }
        }

        // Update input text display
        portInput.setString(portStr);
        freqInput.setString(freqStr);

        // Clear window and draw elements
        window.clear(sf::Color(50, 50, 50)); // Background color
        window.draw(portLabel);
        window.draw(frequencyLabel);
        window.draw(portBox);
        window.draw(freqBox);
        window.draw(portInput);
        window.draw(freqInput);
        window.draw(instructionText); // Draw instruction text
        window.draw(portHintText);    // Draw port hint text
        window.draw(frequencyHintText); // Draw frequency hint text
        window.display();
    }

    // Convert strings to integers
    port      = std::stoi(portStr);
    frequency = std::stoi(freqStr);
}


int main() {
    int port;
    int frequency = 60; // Default value

    // Call the function that displays the window to enter port and frequency
    getUserInput(port, frequency);

    std::cout << "Port: " << port << std::endl;
    std::cout << "Frequency: " << frequency << std::endl;

    // Initialize and start the game
    GameLogique gameLogique(port, frequency);
    gameLogique.runGame();

    return 0;
}
