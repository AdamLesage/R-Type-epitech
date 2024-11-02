/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** EndMenu
*/

#include "EndMenu.hpp"

RType::EndMenu::EndMenu(std::shared_ptr<sf::RenderWindow> window)
{
    _window = window;
    _options= {"Play again", "Exit"};
    _selectedOption = 0;
    if (!_font.loadFromFile(std::string("assets") + PATH_SEPARATOR + "r-type.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
}

RType::EndMenu::~EndMenu()
{
}

void RType::EndMenu::runScene(float &latency)
{
    (void)latency; // Do not used latency
    _window->clear();
    this->displayBackground();
    this->displayEndMenuOptions();
    _window->display();
}

void RType::EndMenu::setGameSelected(const std::string& gameSelected) {
    _gameSelected = gameSelected;
    try {
        std::string fileConfigPath = std::string("config") + PATH_SEPARATOR + _gameSelected + PATH_SEPARATOR + "game_config.cfg";
        _cfg.readFile(fileConfigPath.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return;
    }
}

void RType::EndMenu::displayBackground() {
    sf::Texture texture;
    size_t startPos = 0;
    std::string backgroundSpritePath = _cfg.lookup("Menu.EndMenu.background").c_str();

    std::string from = "/";
    while ((startPos = backgroundSpritePath.find(from, startPos)) != std::string::npos) {
        backgroundSpritePath.replace(startPos, from.length(), PATH_SEPARATOR);
        startPos += std::strlen(PATH_SEPARATOR);
    }

    if (!texture.loadFromFile(backgroundSpritePath)) {
        std::cerr << "Failed to load texture from " << backgroundSpritePath << std::endl;
        return;
    }

    sf::RectangleShape background(sf::Vector2f(1920, 1080));
    background.setTexture(&texture);
    _window->draw(background);
}

void RType::EndMenu::displayEndMenuOptions()
{
    for (size_t i = 0; i < _options.size(); ++i) {
        sf::Text optionText;
        optionText.setFont(_font);
        optionText.setString(_options[i]);
        optionText.setCharacterSize(30);
        optionText.setFillColor(i == _selectedOption ? sf::Color::Red : sf::Color::White);
        optionText.setPosition(100, 200 + i * 50);
        _window->draw(optionText);
    }

    // Handle Up key press for selection
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!_upKeyPressed) {
            _selectedOption = (_selectedOption - 1 + _options.size()) % _options.size();
            _upKeyPressed = true;
        }
    } else {
        _upKeyPressed = false;
    }

    // Handle Down key press for selection
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (!_downKeyPressed) { // Detect first press
            _selectedOption = (_selectedOption + 1) % _options.size();
            _downKeyPressed = true; // Set key state to prevent repeated triggers
        }
    } else {
        _downKeyPressed = false; // Reset when key is released
    }

    // Handle Enter key press for action
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        sf::sleep(sf::milliseconds(150));
        if (_options[_selectedOption] == "Play again") {
            this->_mediator->notify("RenderingEngine", "Play again offline");
        } else if (_options[_selectedOption] == "Exit") {
            this->_mediator->notify("RenderingEngine", "Exit");
        } else {
            std::cerr << "Unsupported action from client";
        }
    }
}
