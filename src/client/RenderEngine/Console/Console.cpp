/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Console
*/

#include "Console.hpp"
#include <sstream>
#include <regex>

RType::Console::Console(std::shared_ptr<sf::RenderWindow> _window) {
    _showDeveloperConsole = false;

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Error loading font");
    }
    this->_typing = false;
    this->window  = _window;
    _inputText.setFont(font);
    _inputText.setFillColor(sf::Color::White);
    _inputText.setPosition(5, window->getSize().y * 0.35);
    for (std::size_t i = 0; i < History.size(); i++) {
        History[i].setFont(font);
        History[i].setFillColor(sf::Color::White);
        History[i].setPosition(0, 0);
    }
    secondContainer.setOutlineColor(sf::Color(150, 150, 150));
    secondContainer.setOutlineThickness(3);
    secondContainer.setFillColor(sf::Color(20, 20, 20, 180)); // Same fill color
    container.setFillColor(sf::Color(20, 20, 20, 180));
    fps = 0;
    FPS.setFillColor(sf::Color::White);
    FPS.setOutlineColor(sf::Color::Black);
    FPS.setOutlineThickness(2);
    FPS.setFont(font);
    FPS.setPosition(5, 5);
    show_fps = false;
}

RType::Console::~Console() {
}

void RType::Console::setMediator(std::shared_ptr<IMediator> mediator) {
    _mediator = mediator;
}

void RType::Console::displayFPS()
{
    float deltaTime = clock.restart().asSeconds();
    fps = 1.0f / deltaTime;  // Calcul des FPS
    FPS.setString(std::to_string(fps));
    window->draw(FPS);
}

void RType::Console::displayDeveloperConsole() {
    if (_showDeveloperConsole == false) // Do not display the console if it's hidden
        return;

    if (_typing) {
    _inputText.setString("> " + _input + "|");
    } else {
        _inputText.setString("> " + _input);
    }

    this->displayContainer();
    this->displayCloseContainerButton();
    if (show_fps)
        displayFPS();
}

void RType::Console::toggleDeveloperConsoleFromEvent(sf::Event& _event) {
    if (_event.type == sf::Event::KeyPressed) {
        if (_event.key.code == sf::Keyboard::F8) {
            this->toggleDeveloperConsole();
            _typing = !_typing;
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
    for (std::size_t i = 0; i < History.size(); i++) {
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


bool processEdit(const std::string& _input) {
    std::regex pattern("^edit_entity\\s+\\d+\\s+\\d+$");

    if (std::regex_match(_input, pattern)) {
        std::istringstream iss(_input);
        std::string command;
        int entityNum1, entityNum2;

        iss >> command >> entityNum1 >> entityNum2;

        std::cout << "Changing skin of entity " << entityNum1 << " whith skin " << entityNum2 << std::endl;
            // entity[i].setTexture(Textures[_camera->listEntityToDisplay[i].sprite.spritePath]);
            // entity[i].setTextureRect(sf::IntRect(_camera->listEntityToDisplay[i].sprite.rectPos[0],
            //                                      _camera->listEntityToDisplay[i].sprite.rectPos[1],
            //                                      _camera->listEntityToDisplay[i].sprite.rectSize[0],
            //                                      _camera->listEntityToDisplay[i].sprite.rectSize[1]));

        return true;
    }

    return false;
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
    if (_input.find("create_entity ") == 0) {
        _mediator->notify("RenderingEngine", _input);
        return true;
    }
    if (_input.find("delete_entity ") == 0) {
        _mediator->notify("RenderingEngine", _input);
        return true;
    }
    if (processEdit(_input))
        return true;
    if (_input == "show_fps") {
        show_fps = true;
        return true;
    }
    if (_input.find("create_wave") == 0) {
        _mediator->notify("RenderingEngine", _input);
        return true;
    }
    if (_input == "god_mode enabled") {
        std::string str = "god_mode 1";
        _mediator->notify("RenderingEngine", str);
        return true;
    }
    if (_input == "god_mode disabled") {
        std::string str = "god_mode 0";
        _mediator->notify("RenderingEngine", str);
        return true;
    }
    if (_input.find("shoot_speed ") == 0) {
        _mediator->notify("RenderingEngine", _input);
        return true;
    }
    if (_input.find("teleport ") == 0) {
        _mediator->notify("RenderingEngine", _input);
        return true;
    }
    if (_input.find("set_lives ") == 0) {
        _mediator->notify("RenderingEngine", _input);
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
                            if (History.size() < 11) {
                                _inputText.setPosition(0, 30 * History.size());
                            } else {
                                History.erase(History.begin());
                                for (std::size_t i = 0; i < History.size(); i++) {
                                    History[i].setPosition(0, 30 * i);
                                }
                                _inputText.setPosition(0, 30 * History.size());
                            }
                            _inputText.setString("  " + _input);
                            History.push_back(_inputText);
                            _input.clear();
                        }
                    } else {
                        if (!_input.empty()) {
                            if (History.size() < 11) {
                                _inputText.setPosition(0, 30 * History.size());
                            } else {
                                History.erase(History.begin());
                                History.erase(History.begin());
                                for (std::size_t i = 0; i < History.size(); i++) {
                                    History[i].setPosition(0, 30 * i);
                                }
                                _inputText.setPosition(0, 30 * History.size());
                            }
                            _inputText.setString("  " + _input);
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
                if (_typing) {
                    _inputText.setString("> " + _input + " |");
                } else {
                    _inputText.setString("> " + _input);
                }
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
