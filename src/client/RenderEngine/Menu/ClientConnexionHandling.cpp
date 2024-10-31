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
    _gameSelected      = "R-Type";
    _gameIndex         = 0;
    _gameList          = {"R-Type", "Platformer"};

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
    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window->close();
            }
            this->retrieveInputTextHost(event);
            this->retrieveInputTextPort(event);
            this->retrieveInputGameSelection(event);
        }
        _window->clear();
        this->displayBackground();
        this->displayInputTextHost();
        this->displayInputTextPort();
        this->displaySubmitButton();
        this->displayError();
        this->displayGameSelection();
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

void RType::ClientConnexionHandling::displayInputTextHost() {
    sf::Text labelHost;
    labelHost.setFont(_font);
    labelHost.setString("Host");
    labelHost.setCharacterSize(24);
    labelHost.setFillColor(sf::Color::Red);
    labelHost.setPosition(1920 / 2 - 100, 1080 / 2 - 85);

    sf::RectangleShape inputTextHost(sf::Vector2f(200, 50));
    inputTextHost.setFillColor(sf::Color(50, 50, 50, 255));
    inputTextHost.setPosition(1920 / 2 - 100, 1080 / 2 - 50);

    // Outline thickness of 2
    if (_inputBoxSelected == "host") {
        inputTextHost.setOutlineThickness(2);
    } else {
        inputTextHost.setOutlineThickness(0);
    }
    inputTextHost.setOutlineColor(sf::Color::Red);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    sf::FloatRect bounds  = inputTextHost.getGlobalBounds();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
        _inputBoxSelected = "host";
    }

    _inputTextHost.setPosition(inputTextHost.getPosition().x + 10, inputTextHost.getPosition().y + 10);

    _window->draw(labelHost);
    _window->draw(inputTextHost);
    _window->draw(_inputTextHost);
}

void RType::ClientConnexionHandling::displayInputTextPort() {
    sf::Text labelPort;
    labelPort.setFont(_font);
    labelPort.setString("Port");
    labelPort.setCharacterSize(24);
    labelPort.setFillColor(sf::Color::Red);
    labelPort.setPosition(1920 / 2 - 100, 1080 / 2 + 15);

    sf::RectangleShape inputTextPort(sf::Vector2f(200, 50));
    inputTextPort.setFillColor(sf::Color(50, 50, 50, 255));
    inputTextPort.setPosition(1920 / 2 - 100, 1080 / 2 + 50);

    // Outline thickness of 2
    if (_inputBoxSelected == "port") {
        inputTextPort.setOutlineThickness(2);
    } else {
        inputTextPort.setOutlineThickness(0);
    }
    inputTextPort.setOutlineColor(sf::Color::Red);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    sf::FloatRect bounds  = inputTextPort.getGlobalBounds();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
        _inputBoxSelected = "port";
    }

    _inputTextPort.setPosition(inputTextPort.getPosition().x + 10, inputTextPort.getPosition().y + 10);

    _window->draw(labelPort);
    _window->draw(inputTextPort);
    _window->draw(_inputTextPort);
}

void RType::ClientConnexionHandling::displaySubmitButton() {
    sf::RectangleShape submitButtonRect(sf::Vector2f(100, 50));
    submitButtonRect.setPosition(1920 / 2 - 50, 1080 / 2 + 250);

    sf::Text submitButton;
    submitButton.setFont(_font);
    submitButton.setString("Submit");
    submitButton.setCharacterSize(24);
    submitButton.setFillColor(sf::Color::White);
    submitButton.setStyle(sf::Text::Bold);
    submitButton.setOutlineColor(sf::Color::Red);
    submitButton.setPosition(submitButtonRect.getPosition().x
                                 + (submitButtonRect.getSize().x - submitButton.getLocalBounds().width) / 2,
                             submitButtonRect.getPosition().y
                                 + (submitButtonRect.getSize().y - submitButton.getLocalBounds().height) / 2
                                 - submitButton.getLocalBounds().top);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    sf::FloatRect bounds  = submitButtonRect.getGlobalBounds();

    // Hover effect for the button
    if (bounds.contains(static_cast<sf::Vector2f>(mousePos)) == true) {
        submitButtonRect.setFillColor(sf::Color(139, 0, 0)); // Dark red
        submitButtonRect.setOutlineColor(sf::Color::White);
        submitButtonRect.setOutlineThickness(1);
    } else { // Set normal settings for the button
        submitButtonRect.setOutlineThickness(0);
        submitButtonRect.setFillColor(sf::Color::Red);
    }

    // If client can click
    if (_interactionClock.getElapsedTime() >= _interactionDelay) {
        if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)
             && bounds.contains(static_cast<sf::Vector2f>(mousePos)))
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

            if (_inputBoxSelected == "host") {
                _inputBoxSelected = "port";
            } else if (_inputBoxSelected == "port") {
                _inputBoxSelected = "gameSelection";
            } else if (_inputBoxSelected == "gameSelection") {
                if (this->areHostAndPortValid()) {
                    _window->close();
                    return;
                } else {
                    _invalidPortOrHost = true;
                }
            }
            _interactionClock.restart();
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

void RType::ClientConnexionHandling::displayGameSelection() {
    // Gestion du label "Game"
    sf::Text labelGame;
    labelGame.setFont(_font);
    labelGame.setString("Game");
    labelGame.setCharacterSize(24);
    labelGame.setFillColor(sf::Color::Red);
    labelGame.setPosition(1920 / 2 - 100, 1080 / 2 + 115);

    // Input field pour le nom du jeu
    sf::RectangleShape inputTextGame(sf::Vector2f(200, 50));
    inputTextGame.setFillColor(sf::Color(50, 50, 50, 255));
    inputTextGame.setPosition(1920 / 2 - 100, 1080 / 2 + 150);

    if (_inputBoxSelected == "gameSelection") {
        inputTextGame.setOutlineThickness(2);
    } else {
        inputTextGame.setOutlineThickness(0);
    }
    inputTextGame.setOutlineColor(sf::Color::Red);

    // Détection du clic sur l'input field pour la sélection
    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    sf::FloatRect bounds  = inputTextGame.getGlobalBounds();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
        _inputBoxSelected = "gameSelection";
    }

    sf::Text arrowLeft;
    arrowLeft.setFont(_font);
    arrowLeft.setString("<");
    arrowLeft.setCharacterSize(30); // Taille agrandie
    arrowLeft.setFillColor(sf::Color::White);
    arrowLeft.setPosition(inputTextGame.getPosition().x - 50, inputTextGame.getPosition().y + 5);

    sf::Text arrowRight;
    arrowRight.setFont(_font);
    arrowRight.setString(">");
    arrowRight.setCharacterSize(30); // Taille agrandie
    arrowRight.setFillColor(sf::Color::White);
    arrowRight.setPosition(inputTextGame.getPosition().x + inputTextGame.getSize().x + 20,
                           inputTextGame.getPosition().y + 5);

    sf::FloatRect leftBounds  = arrowLeft.getGlobalBounds();
    sf::FloatRect rightBounds = arrowRight.getGlobalBounds();

    static sf::Clock changeClock;
    const sf::Time delay = sf::milliseconds(300);

    // Click detection
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && changeClock.getElapsedTime() > delay) {
        if (leftBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
            _gameIndex    = (_gameIndex - 1 + _gameList.size()) % _gameList.size();
            _gameSelected = _gameList[_gameIndex];
            changeClock.restart();
        } else if (rightBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
            _gameIndex    = (_gameIndex + 1) % _gameList.size();
            _gameSelected = _gameList[_gameIndex];
            changeClock.restart();
        }
    }

    // Display text game selected
    sf::Text gameText;
    gameText.setFont(_font);
    gameText.setString(_gameSelected);
    gameText.setCharacterSize(24);
    gameText.setFillColor(sf::Color::White);
    gameText.setPosition(inputTextGame.getPosition().x + 10, inputTextGame.getPosition().y + 10);

    _window->draw(labelGame);
    _window->draw(inputTextGame);
    _window->draw(gameText);
    _window->draw(arrowLeft);
    _window->draw(arrowRight);
}

void RType::ClientConnexionHandling::retrieveInputTextHost(const sf::Event& event) {
    if (_inputBoxSelected == "host" && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !_inputTextHost.getString().isEmpty()) {
            // Remove the last character if backspace
            std::string currentText = _inputTextHost.getString();
            currentText.pop_back();
            _inputTextHost.setString(currentText);
        } else if (event.text.unicode < 128) {
            // Add char if user types
            _inputTextHost.setString(_inputTextHost.getString() + static_cast<char>(event.text.unicode));
        }
    }
}

void RType::ClientConnexionHandling::retrieveInputTextPort(const sf::Event& event) {
    if (_inputBoxSelected == "port" && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !_inputTextPort.getString().isEmpty()) {
            // Remove the last character if backspace
            std::string currentText = _inputTextPort.getString();
            currentText.pop_back();
            _inputTextPort.setString(currentText);
        } else if (event.text.unicode < 128) {
            // Add char if user types
            _inputTextPort.setString(_inputTextPort.getString() + static_cast<char>(event.text.unicode));
        }
    }
}

void RType::ClientConnexionHandling::retrieveInputGameSelection(const sf::Event& event) {
    if (_inputBoxSelected == "gameSelection" && event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Right:
            _gameSelected = "Platformer";
            break;
        case sf::Keyboard::Left:
            _gameSelected = "R-Type";
            break;
        default:
            break;
        }
    }
}

bool RType::ClientConnexionHandling::areHostAndPortValid() {
    if ((int)this->getServerPort() < 1024 || (int)this->getServerPort() > 65534) {
        std::cerr << "Port must be between 1024 and 65535" << std::endl;
        return false;
    }
    if (std::string(this->getHost()).length() < 7) {
        std::cerr << "Host must be at least 7 characters long" << std::endl;
        return false;
    }
    return true;
}
