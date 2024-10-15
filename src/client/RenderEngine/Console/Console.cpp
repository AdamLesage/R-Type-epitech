/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Console
*/

#include "Console.hpp"

RType::Console::Console(std::shared_ptr<sf::RenderWindow> _window, sf::Event _event) {
    _showDeveloperConsole = false;

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Error loading font");
    }
    this->_typing = false;
    this->window  = _window;
    _inputText.setString(">");
    _inputText.setFont(font);
    _inputText.setFillColor(sf::Color::White);
    _inputText.setPosition(5, window->getSize().y * 0.35);
    for (int i = 0; i < History.size(); i++) {
        History[i].setFont(font);
        History[i].setFillColor(sf::Color::White);
        History[i].setPosition(0, 0);
    }
    secondContainer.setOutlineColor(sf::Color(150, 150, 150));
    secondContainer.setOutlineThickness(3);
    secondContainer.setFillColor(sf::Color(20, 20, 20, 180)); // Same fill color
    container.setFillColor(sf::Color(20, 20, 20, 180));
}

RType::Console::~Console() {
}

void RType::Console::displayDeveloperConsole() {
    if (_showDeveloperConsole == false) // Do not display the console if it's hidden
        return;

    // Display the console
    this->displayContainer();
    this->displayCloseContainerButton();
}

void RType::Console::toggleDeveloperConsoleFromEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F8) {
            this->toggleDeveloperConsole();
            _typing = true;
        }
    }
}

void RType::Console::displayContainer() {
    unsigned int width  = window->getSize().x;
    unsigned int height = window->getSize().y;

    if (width < 900 || height < 800) return;

    unsigned int consoleWidth  = width;
    unsigned int consoleHeight = height * 0.36;
    unsigned int secondContainerHeight = consoleHeight * 0.11;

    container.setSize(sf::Vector2f(consoleWidth, consoleHeight));
    container.setPosition(0, 0);
    secondContainer.setSize(sf::Vector2f(consoleWidth, secondContainerHeight));
    secondContainer.setPosition(0, consoleHeight);
    _inputText.setPosition(10, consoleHeight);

    window->draw(container);
    window->draw(secondContainer);
    window->draw(_inputText);
    for (int i = 0; i < History.size(); i++) {
        window->draw(History[i]);
    }
}


void RType::Console::checkClick()
{
    sf::Mouse mouse;
    sf::Vector2f mousPos;
    mousPos.x = mouse.getPosition(*this->window.get()).x;
    mousPos.y = mouse.getPosition(*this->window.get()).y;
    if (mouse.isButtonPressed(sf::Mouse::Button::Left)) {
        if (this->secondContainer.getGlobalBounds().contains(mousPos)) {
            this->_typing = true;
        } else {
            this->_typing = false;
        }
    }
}

bool RType::Console::isCommand()
{
    if (_input == "clear") {
        History.clear();
        return true;
    }
    if (_input == "quit") {
        window->close();
        return true;
    }
    return false;
}

bool RType::Console::checkInput()
{
    checkClick();  // Check if the user clicked inside the input box
    if (this->_typing == true) {
        while (this->window.get()->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8) {
                    if (!_input.empty()) {
                        _input.pop_back();
                    }
                }
                if (event.text.unicode == 13) {
                    if (isCommand()) {
                        if (!_input.empty()) {
                            if (History.size() < 12) {
                                _inputText.setPosition(0, 30 * History.size());
                            } else {
                                History.erase(History.begin());
                                for (int i = 0; i < History.size(); i++) {
                                    History[i].setPosition(0, 30 * i);
                                }
                                _inputText.setPosition(0, 30 * History.size());
                            }
                            History.push_back(_inputText);
                            _input.clear();
                        }
                    } else {
                        if (!_input.empty()) {
                            if (History.size() < 12) {
                                _inputText.setPosition(0, 30 * History.size());
                            } else {
                                History.erase(History.begin());
                                History.erase(History.begin());
                                for (int i = 0; i < History.size(); i++) {
                                    History[i].setPosition(0, 30 * i);
                                }
                                _inputText.setPosition(0, 30 * History.size());
                            }
                            History.push_back(_inputText);
                            _inputText.setString("  Command not found");
                            _inputText.setPosition(0, 30 * History.size());
                            History.push_back(_inputText);
                            _input.clear();
                        }
                    }
                }
                else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    _input.push_back(static_cast<char>(event.text.unicode));
                }
                _inputText.setString("> " + _input);
                return true;
            }
        }
    }
    return false;
}


void RType::Console::displayCloseContainerButton() {
    unsigned int width  = window->getSize().x;
    unsigned int height = window->getSize().y;
    if (width < 800 || height < 600) return;
    unsigned int consoleWidth  = width;
    unsigned int consoleHeight = height * 0.4;
    unsigned int closeBtnSize = 20;
    unsigned int closeBtnPosX = consoleWidth - closeBtnSize;
    sf::RectangleShape closeBtn(sf::Vector2f(closeBtnSize, closeBtnSize));
    closeBtn.setOutlineColor(sf::Color::White);
    closeBtn.setOutlineThickness(2);
    closeBtn.setFillColor(sf::Color(255, 0, 0, 128));

    closeBtn.setPosition(closeBtnPosX - 2, 2);
    window->draw(closeBtn);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (closeBtn.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                static_cast<float>(mousePos.y))) {
            this->toggleDeveloperConsole();
            return;
        }
    }
}

int main() {
    std::shared_ptr<sf::RenderWindow> window;
    sf::Event event;
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type");
    RType::Console console(window, event);

    console.toggleDeveloperConsole();
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
            }
            console.toggleDeveloperConsoleFromEvent(event);
            console.checkInput();
        }
        window->clear(sf::Color::White);
        console.displayDeveloperConsole();
        window->display();
    }
}