/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** EndMenu
*/

#include "EndMenu.hpp"

RType::EndMenu::EndMenu(std::shared_ptr<sf::RenderWindow> window) {
    _window         = window;
    _options        = {"Play again", "Exit"};
    _selectedOption = 0;
    if (!_font.loadFromFile(std::string("assets") + PATH_SEPARATOR + "r-type.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
}

RType::EndMenu::~EndMenu() {
}

void RType::EndMenu::runScene(float& latency) {
    (void)latency; // Do not used latency
    _window->clear();
    this->displayBackground();
    this->displayEndMenuOptions();
    this->displayFinalScore();
    _window->display();
}

void RType::EndMenu::setGameSelected(const std::string& gameSelected) {
    _gameSelected = gameSelected;
    try {
        std::string fileConfigPath =
            std::string("config") + PATH_SEPARATOR + _gameSelected + PATH_SEPARATOR + "game_config.cfg";
        _cfg.readFile(fileConfigPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                  << std::endl;
        return;
    }
}

void RType::EndMenu::displayBackground() {
    sf::Texture texture;
    size_t startPos                  = 0;
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

void RType::EndMenu::displayEndMenuOptions() {
    for (size_t i = 0; i < _options.size(); ++i) {
        sf::Text optionText;
        optionText.setFont(_font);
        optionText.setString(_options[i]);
        optionText.setCharacterSize(30);
        optionText.setFillColor(i == _selectedOption ? sf::Color::Red : sf::Color::Magenta);
        optionText.setPosition(100, 200 + i * 50);
        _window->draw(optionText);
    }

    // Handle Up key press for selection
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!_upKeyPressed) {
            _selectedOption = (_selectedOption - 1 + _options.size()) % _options.size();
            _upKeyPressed   = true;
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

void RType::EndMenu::setCamera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}

void RType::EndMenu::displayFinalScore()
{
    if (_camera == nullptr) {
        std::cerr << "[Debug] _camera is nullptr, aborting displayFinalScore." << std::endl;
        return;
    }

    sf::RenderWindow& win = *_window;
    std::vector<sf::Text> finalScores;
    sf::Text scoreTitle;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    float totalWidth = 0.0f;
    sf::Font scoreFont;

    if (!scoreFont.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font from path: " << fontPath << std::endl;
        return;
    }
    scoreTitle.setFont(scoreFont);
    scoreTitle.setString("Final Score:");
    scoreTitle.setCharacterSize(48);
    scoreTitle.setFillColor(sf::Color::White);

    std::cerr << "[Debug] Loading scores from _camera->listEntityToDisplay." << std::endl;
    for (const auto& entityInfo : _camera->listEntityToDisplay) {
        std::cerr << "[Debug] Checking entity with score: " << entityInfo.score.score << std::endl;
        if (entityInfo.score.score > 0) {
            sf::Text finalScore;
            finalScore.setFont(scoreFont);
            finalScore.setString(std::to_string(entityInfo.score.score));
            finalScore.setCharacterSize(38);
            finalScore.setFillColor(sf::Color::White);

            float textWidth = finalScore.getLocalBounds().width;
            totalWidth += finalScore.getLocalBounds().width + 10;
            std::cerr << "[Debug] Added score " << entityInfo.score.score 
                      << " with width " << textWidth << ". Total width now: " << totalWidth << std::endl;
            finalScores.push_back(finalScore);
        }
    }

    if (finalScores.empty()) {
        std::cerr << "[Debug] No scores to display, finalScores vector is empty." << std::endl;
        return;
    }

    float startX = (win.getSize().x - totalWidth) / 2.0f;
    float yOffset = 80.0f;

    float titleX = (win.getSize().x - scoreTitle.getLocalBounds().width) / 2.0f;
    scoreTitle.setPosition(titleX, 10.0f);
    win.draw(scoreTitle);

    std::cerr << "[Debug] Drawing scores starting at X position: " << startX 
              << ", Y offset: " << yOffset << std::endl;
    for (auto& finalScore : finalScores) {
        std::cerr << "[Debug] Drawing score at position X: " << startX 
                  << ", Y: " << yOffset << " with text: " << finalScore.getString().toAnsiString() << std::endl;
        finalScore.setPosition(startX, yOffset);
        win.draw(finalScore);
        startX += finalScore.getLocalBounds().width + 10;
    }
}
