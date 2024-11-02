/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** ClientConnexionHandling
*/

#if defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
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
    _isOffline         = false;

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
        this->displayModeOffline();
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

    // Ajouter un contour de 2 si sélectionné
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

    // Ajouter un contour de 2 si sélectionné
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
    submitButtonRect.setFillColor(sf::Color::Red);
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

    if (((sf::Mouse::isButtonPressed(sf::Mouse::Left)
          && bounds.contains(static_cast<sf::Vector2f>(mousePos)) == true)
         || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))) {
        if (this->areHostAndPortValid() == true) {
            if (!(_gameSelected == "Platformer" && !_isOffline)) {
                _window->close();
                return;
            }
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

void RType::ClientConnexionHandling::displayGameSelection() {
    sf::Text labelGame;
    labelGame.setFont(_font);
    labelGame.setString("Game");
    labelGame.setCharacterSize(24);
    labelGame.setFillColor(sf::Color::Red);
    labelGame.setPosition(1920 / 2 - 100, 1080 / 2 + 115);

    sf::RectangleShape inputTextGame(sf::Vector2f(200, 50));
    inputTextGame.setFillColor(sf::Color(50, 50, 50, 255));
    inputTextGame.setPosition(1920 / 2 - 100, 1080 / 2 + 150);

    // Add a 2-pixel outline if selected
    if (_inputBoxSelected == "gameSelection") {
        inputTextGame.setOutlineThickness(2);
    } else {
        inputTextGame.setOutlineThickness(0);
    }
    inputTextGame.setOutlineColor(sf::Color::Red);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    sf::FloatRect bounds  = inputTextGame.getGlobalBounds();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
        _inputBoxSelected = "gameSelection";
    }

    sf::Text gameText;
    gameText.setFont(_font);
    gameText.setString(_gameSelected);
    gameText.setCharacterSize(24);
    gameText.setFillColor(sf::Color::White);
    gameText.setPosition(inputTextGame.getPosition().x + 10, inputTextGame.getPosition().y + 10);

    _window->draw(labelGame);
    _window->draw(inputTextGame);
    _window->draw(gameText);

    // Display warning message if Platformer is selected in online mode
    if (!_isOffline && _gameSelected == "Platformer") {
        sf::Text warningText;
        warningText.setFont(_font);
        warningText.setString("Platformer is not available online");
        warningText.setCharacterSize(24);
        warningText.setFillColor(sf::Color::Red);
        warningText.setPosition(1920 / 2 - warningText.getLocalBounds().width / 2, 1080 / 2 + 200);

        _window->draw(warningText);
    }
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

void RType::ClientConnexionHandling::displayModeOffline() {
    static sf::Clock clickClock;
    const sf::Time debounceTime = sf::milliseconds(200);

    // create button shape
    sf::RectangleShape button(sf::Vector2f(150, 60));
    button.setPosition(1920 / 2 - button.getSize().x / 2, 1080 / 2 - 175);
    button.setOutlineThickness(3);
    button.setOutlineColor(sf::Color::White);

    sf::Color colorNormal = _isOffline ? sf::Color(200, 50, 50) : sf::Color(50, 200, 50);
    sf::Color colorHover  = _isOffline ? sf::Color(255, 100, 100) : sf::Color(100, 255, 100);

    sf::Vector2i mousePos      = sf::Mouse::getPosition(*_window);
    sf::FloatRect buttonBounds = button.getGlobalBounds();

    // If mouse is hover
    if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
        button.setFillColor(colorHover);

        // If button is clicked and can be clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickClock.getElapsedTime() > debounceTime) {
            _isOffline = !_isOffline;
            clickClock.restart();
        }
    } else {
        button.setFillColor(colorNormal);
    }

    // Button text
    sf::Text buttonText;
    buttonText.setFont(_font);
    buttonText.setString(_isOffline ? "Offline" : "Online");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        button.getPosition().x + (button.getSize().x - textBounds.width) / 2 - textBounds.left,
        button.getPosition().y + (button.getSize().y - textBounds.height) / 2 - textBounds.top);

    _window->draw(button);
    _window->draw(buttonText);
}
