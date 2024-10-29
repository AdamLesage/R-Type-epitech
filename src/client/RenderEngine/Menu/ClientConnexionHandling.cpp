/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ClientConnexionHandling
*/

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define LIB_EXTENSION ".dll"
#define PATH_SEPARATOR "\\"
#else
#include <dlfcn.h>
#define LIB_EXTENSION ".so"
#define PATH_SEPARATOR "/"
#endif

#include "ClientConnexionHandling.hpp"

RType::ClientConnexionHandling::ClientConnexionHandling(std::string host, unsigned short server_port) {
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type");
    _window->setFramerateLimit(60);
    _inputBoxSelected  = "host";
    _invalidPortOrHost = false;

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    _font.loadFromFile(fontPath);

    _inputTextHost.setString(host);
    _inputTextHost.setFont(_font);
    _inputTextHost.setCharacterSize(24);
    _inputTextHost.setFillColor(sf::Color::White);

    _inputTextPort.setString(std::to_string(server_port));
    _inputTextPort.setFont(_font);
    _inputTextPort.setCharacterSize(24);
    _inputTextPort.setFillColor(sf::Color::White);
}

RType::ClientConnexionHandling::~ClientConnexionHandling() {
}

void RType::ClientConnexionHandling::displayConnexionWindow() {
    sf::Text labelHost;
    labelHost.setFont(_font);
    labelHost.setString("Host");
    labelHost.setCharacterSize(24);
    labelHost.setFillColor(sf::Color::Red);
    labelHost.setPosition(1920 / 2 - 100, 1080 / 2 - 85);

    sf::Text labelPort;
    labelPort.setFont(_font);
    labelPort.setString("Port");
    labelPort.setCharacterSize(24);
    labelPort.setFillColor(sf::Color::Red);
    labelPort.setPosition(1920 / 2 - 100, 1080 / 2 + 15);

    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->close();
            }
            this->retrieveInputTextHost(event);
            this->retrieveInputTextPort(event);
        }
        _window->clear();
        this->displayBackground();
        this->displayInputTextHost(labelHost, labelPort);
        this->displayInputTextPort(labelPort, labelHost);
        this->displaySubmitButton();
        this->displayError();
        _window->display();
    }
}

void RType::ClientConnexionHandling::displayBackground() {
    sf::Texture texture;
    std::string spritePath =
        "assets" + std::string(PATH_SEPARATOR) + "background" + std::string(PATH_SEPARATOR) + "menu.jpg";
    if (!texture.loadFromFile(spritePath)) {
        std::cerr << "Failed to load texture from " << spritePath << std::endl;
        return;
    }
    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setTexture(&texture);
    _window->draw(background);
}

void RType::ClientConnexionHandling::displayInputTextHost(sf::Text labelHost, sf::Text labelPort) {
    sf::RectangleShape inputTextHost(sf::Vector2f(200, 50));
    inputTextHost.setFillColor(sf::Color(50, 50, 50, 255));
    inputTextHost.setPosition(1920 / 2 - 100, 1080 / 2 - 50);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    sf::FloatRect bounds  = inputTextHost.getGlobalBounds();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
        _inputBoxSelected = "host";
        _isHostSelected = true;
        _isPortSelected = false;
    }

    labelHost.setFillColor(_isHostSelected ? sf::Color::Green : sf::Color::Red);
    labelPort.setFillColor(_isPortSelected ? sf::Color::Red : sf::Color::Red);

    _inputTextHost.setPosition(inputTextHost.getPosition().x + 10, inputTextHost.getPosition().y + 10);

    _window->draw(labelHost);
    _window->draw(inputTextHost);
    _window->draw(_inputTextHost);
}

void RType::ClientConnexionHandling::displayInputTextPort(sf::Text labelPort, sf::Text labelHost) {
    sf::RectangleShape inputTextPort(sf::Vector2f(200, 50));
    inputTextPort.setFillColor(sf::Color(50, 50, 50, 255));
    inputTextPort.setPosition(1920 / 2 - 100, 1080 / 2 + 50);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    sf::FloatRect bounds  = inputTextPort.getGlobalBounds();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
        _inputBoxSelected = "port";
        _isPortSelected = true;
        _isHostSelected = false;
    }

    labelPort.setFillColor(_isPortSelected ? sf::Color::Green : sf::Color::Red);
    labelHost.setFillColor(_isHostSelected ? sf::Color::Red : sf::Color::Red);

    _inputTextPort.setPosition(inputTextPort.getPosition().x + 10, inputTextPort.getPosition().y + 10);

    _window->draw(labelPort);
    _window->draw(inputTextPort);
    _window->draw(_inputTextPort);
}

void RType::ClientConnexionHandling::displaySubmitButton() {
    sf::RectangleShape submitButtonRect(sf::Vector2f(100, 50));
    submitButtonRect.setFillColor(sf::Color(50, 50, 50, 255));
    submitButtonRect.setPosition(1920 / 2 - 50, 1080 / 2 + 150);

    sf::Text submitButton;
    submitButton.setFont(_font);
    submitButton.setString("Submit");
    submitButton.setCharacterSize(24);
    submitButton.setFillColor(sf::Color::Red);
    submitButton.setPosition(submitButtonRect.getPosition().x
                                 + (submitButtonRect.getSize().x - submitButton.getLocalBounds().width) / 2,
                             submitButtonRect.getPosition().y
                                 + (submitButtonRect.getSize().y - submitButton.getLocalBounds().height) / 2
                                 - submitButton.getLocalBounds().top);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    sf::FloatRect bounds  = submitButtonRect.getGlobalBounds();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
        if (this->areHostAndPortValid() == true) {
            _window->close();
            return;
        } else {
            _invalidPortOrHost = true;
        }
    }

    _window->draw(submitButtonRect);
    _window->draw(submitButton);
}

void RType::ClientConnexionHandling::displayError() {
    if (_invalidPortOrHost == false) {
        return;
    }

    sf::Text error;
    error.setFont(_font);
    error.setString("Invalid port or host");
    error.setCharacterSize(24);
    error.setFillColor(sf::Color::Red);
    error.setPosition(1920 / 2 - error.getLocalBounds().width / 2, 1080 / 2 + 200);

    _window->draw(error);
}

void RType::ClientConnexionHandling::retrieveInputTextHost(const sf::Event& event) {
    if (_inputBoxSelected == "host" && event.type == sf::Event::TextEntered) {
        std::string currentText = _inputTextHost.getString();

        if (event.text.unicode == 8) {
            if (!currentText.empty()) {
                currentText.pop_back();
                _inputTextHost.setString(currentText);
            }
        } else if (event.text.unicode < 128) {
            _inputTextHost.setString(currentText + static_cast<char>(event.text.unicode));
        }
    }
}

void RType::ClientConnexionHandling::retrieveInputTextPort(const sf::Event& event) {
    if (_inputBoxSelected == "port" && event.type == sf::Event::TextEntered) {
        std::string currentText = _inputTextPort.getString();

        if (event.text.unicode == 8) {
            if (!currentText.empty()) {
                currentText.pop_back();
                _inputTextPort.setString(currentText);
            }
        } else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            _inputTextPort.setString(currentText + static_cast<char>(event.text.unicode));
        }
    }
}

bool RType::ClientConnexionHandling::areHostAndPortValid() {
    if (this->getServerPort() < 1024) {
        std::cerr << "Port must be between 1024 and 65535" << std::endl;
        return false;
    }
    if (std::string(this->getHost()).length() < 7) {
        std::cerr << "Host must be at least 7 characters long" << std::endl;
        return false;
    }
    return true;
}
