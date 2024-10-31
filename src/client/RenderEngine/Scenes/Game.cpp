/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Game
*/
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>

RType::Game::Game(std::shared_ptr<sf::RenderWindow> _window, std::string scenePath, std::shared_ptr<Registry> registry)
    : currentFrame(1), frameDuration(0.05f), animationComplete(false), _registry(registry) {
    this->window = _window;
    this->_mediator = nullptr;
    isShooting = false;

    try {
        _cfg.readFile(scenePath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        throw std::runtime_error("Error loading config file");
    }

    if (!font.loadFromFile(std::string("assets") + PATH_SEPARATOR + "r-type.ttf")) {
        throw std::runtime_error("Error loading font");
    }

    try {
        // Retrieve background paths from config file
        libconfig::Setting& backgroundSettings = _cfg.lookup("Menu.Game.backgrounds");

        // Resize backgroundTextures to match the number of backgrounds
        backgroundTextures.resize(backgroundSettings.getLength());

        for (size_t i = 0; i < backgroundTextures.size(); i++) { // Load all backgrounds textures
            libconfig::Setting& backgroundSetting = backgroundSettings[i];
            // Clean path to be Linux/Windows compatible
            std::string backgroundPath = backgroundSetting["path"];
            int transparency = backgroundSetting["transparency"];
            #ifdef _WIN32
                std::replace(backgroundPath.begin(), backgroundPath.end(), '/', '\\');
            #else
                std::replace(backgroundPath.begin(), backgroundPath.end(), '\\', '/');
            #endif

            if (!backgroundTextures[i].loadFromFile(backgroundPath)) {
                throw std::runtime_error("Error loading backgroundTexture " + std::to_string(i + 1));
            }

            backgrounds.push_back(sf::RectangleShape(sf::Vector2f(window->getSize().x, window->getSize().y)));
            backgrounds[i].setTexture(&backgroundTextures[i]);
            backgrounds[i].setPosition(sf::Vector2f(0, 0));
            if (transparency != 0) {
                backgrounds[i].setFillColor(sf::Color(255, 255, 255, transparency)); // Set transparency
            }
        }
    } catch (const libconfig::SettingNotFoundException& e) {
        throw std::runtime_error("Error loading background settings");
    }



    // Background for colorblind filters
    backgrounds.push_back(sf::RectangleShape(sf::Vector2f(1920, 1080)));
    backgrounds[backgrounds.size() - 1].setTexture(&backgroundTextures[1]);
    backgrounds[backgrounds.size() - 1].setPosition(sf::Vector2f(1920, 0));


    // Set up colorblind shaders
    std::vector<std::string> shaderNames = {
        "Deuteranopia_shader.frag",
        "Protanopia_shader.frag",
        "Tritanopia_shader.frag",
        "Achromatopsia_shader.frag",
        "Normal_shader.frag"
    };
    // Load all shaders
    try {
        for (size_t i = 0; i < shaderNames.size(); ++i) {
            if (!colorblindShader[i].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + shaderNames[i], sf::Shader::Fragment)) {
                throw std::runtime_error("Error loading " + shaderNames[i]);
            }
        }
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Error loading shaders");
    }
    settings      = std::make_shared<Settings>(window);
    console       = std::make_shared<Console>(window, RenderTexture);
    RenderTexture = std::make_shared<sf::RenderTexture>();
    RenderTexture->create(1920, 1080);
    BackgroundClock.restart();
    _camera = std::make_shared<Camera>();
    _currentGame = std::make_shared<DoodleJump>();
}

RType::Game::~Game() {
}

void RType::Game::displayPiou() {
    sf::Text piouText;
    piouText.setFont(font);
    piouText.setString("Piou");
    piouText.setCharacterSize(48);
    piouText.setFillColor(sf::Color::White);
    piouText.setStyle(sf::Text::Bold);
    piouText.setPosition(1920 / 2 - 40, 900);
    RenderTexture->draw(piouText);
}

void RType::Game::ShootSound() {
    libconfig::Config cfg;

    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        exit(84);
    }
    std::string keyValue = settings->get_key_value(cfg, "Keys7");
    if (keyValue == "ON") {
        piou = true;
    }
    _mediator->notify("RenderingEngine", "ShootSound");
}

void RType::Game::DisplaySkipIntro() {
    sf::Text skipIntro;
    skipIntro.setFont(font);
    skipIntro.setString("Press Space to skip intro");
    skipIntro.setCharacterSize(48);
    skipIntro.setFillColor(sf::Color::White);
    skipIntro.setStyle(sf::Text::Bold);
    skipIntro.setPosition(1920 / 2 - 200, 1080 - 100);
    RenderTexture->draw(skipIntro);
}

void RType::Game::play() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                settings->displaySettings(true);
            }
            console->toggleDeveloperConsoleFromEvent(event);
            console->checkInput();
        }
    }

    _systems.control_system(*window.get(), _mediator, std::bind(&RType::Game::ShootSound, this));

    window->clear();
    if (this->isGameOffline() == true) {
        _currentGame->setMediator(_mediator);
        this->_currentGame->handleOfflineGame();
    }


    // Move backgrounds
    libconfig::Setting& backgroundSettings = _cfg.lookup("Menu.Game.backgrounds");
    for (size_t i = backgroundSettings.getLength() - 1; i > 0; i--) { // Browse backwards to have the same order than in the config file
        int speedX = backgroundSettings[i]["movingSpeedX"];
        int speedY = backgroundSettings[i]["movingSpeedY"];

        backgrounds[i].move(speedX, speedY);
        if (backgrounds[i].getPosition().x < -1920) backgrounds[i].setPosition(1920, 0);
        if (backgrounds[i].getPosition().x > 1920) backgrounds[i].setPosition(-1920, 0);
        if (backgrounds[i].getPosition().y < -1080) backgrounds[i].setPosition(0, 1080);
        if (backgrounds[i].getPosition().y > 1080) backgrounds[i].setPosition(0, -1080);

    }
    BackgroundClock.restart();

    for (size_t i = 0; i < backgrounds.size(); i++) {
        RenderTexture->draw(backgrounds[i]);
    }
    this->set_texture();
    for (int i = 0; i < (int)entity.size(); i++) {
        RenderTexture->draw(entity[i]);
    }
    if (piou) {
        displayPiou();
        piou = false;
    }
    RenderTexture->display();
    this->handleColorblind();
    console->displayDeveloperConsole();
    displayEnemyHealth(*window.get());
    displayPlayerHealth(*window.get());
    window->display();
}

void RType::Game::handleColorblind() {
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    sf::Sprite sprite(RenderTexture->getTexture());
    std::string colorblind = settings->get_key_value(cfg, "Keys8");
    if (colorblind.find("Deuteranopia") != std::string::npos) {
        window->draw(sprite, &colorblindShader[0]);
    } else if (colorblind.find("Protanopia") != std::string::npos) {
        window->draw(sprite, &colorblindShader[1]);
    } else if (colorblind.find("Tritanopia") != std::string::npos) {
        window->draw(sprite, &colorblindShader[2]);
    } else if (colorblind.find("Achromatopsia") != std::string::npos) {
        window->draw(sprite, &colorblindShader[3]);
    } else {
        window->draw(sprite, &colorblindShader[4]);
    }
}

sf::Vector2f RType::Game::convertToVector2f(const Size& size) {
    return sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

sf::Vector2f RType::Game::convertToVector2fb(const Position& pos) {
    return sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y));
}

void RType::Game::set_texture() {
    std::lock_guard<std::mutex> lock(*this->_mutex.get());
    entity.clear();
    window->clear();
    if (_camera == nullptr) return;
    if (this->isGameOffline() == true) { // If game is offline, camera is set in the game
        this->_camera = _currentGame->getCamera();
    }

    for (size_t i = 0; i < _camera->listEntityToDisplay.size(); i++) {
        entity.push_back(sf::RectangleShape(convertToVector2f(_camera->listEntityToDisplay[i].size)));
    }

    for (size_t i = 0; i < _camera->listEntityToDisplay.size(); i++) {
        if (Textures.find(_camera->listEntityToDisplay[i].sprite.spritePath)
            != Textures.end()) { // If texture already loaded
            entity[i].setTexture(Textures[_camera->listEntityToDisplay[i].sprite.spritePath]);
            entity[i].setTextureRect(sf::IntRect(_camera->listEntityToDisplay[i].sprite.rectPos[0],
                                                 _camera->listEntityToDisplay[i].sprite.rectPos[1],
                                                 _camera->listEntityToDisplay[i].sprite.rectSize[0],
                                                 _camera->listEntityToDisplay[i].sprite.rectSize[1]));
            entity[i].setPosition(convertToVector2fb(_camera->listEntityToDisplay[i].position));
        } else { // If texture not loaded
            sf::Texture* texture = new sf::Texture();
            texture->loadFromFile(_camera->listEntityToDisplay[i].sprite.spritePath);
            Textures.insert(std::make_pair(_camera->listEntityToDisplay[i].sprite.spritePath, texture));
            entity[i].setTexture(Textures[_camera->listEntityToDisplay[i].sprite.spritePath]);
            entity[i].setTextureRect(sf::IntRect(_camera->listEntityToDisplay[i].sprite.rectPos[0],
                                                 _camera->listEntityToDisplay[i].sprite.rectPos[1],
                                                 _camera->listEntityToDisplay[i].sprite.rectSize[0],
                                                 _camera->listEntityToDisplay[i].sprite.rectSize[1]));
            entity[i].setPosition(convertToVector2fb(_camera->listEntityToDisplay[i].position));
        }
    }
}

void RType::Game::runScene() {
    sf::RectangleShape rectangleshape;
    sf::Texture texture;

    if (this->cinematicsClock == nullptr) {
        cinematicsClock = std::make_unique<sf::Clock>();
        console->setMediator(std::shared_ptr<IMediator>(this->_mediator));
    }

    if (!window) {
        std::cerr << "Error: Window not initialized!" << std::endl;
        return;
    }

    if (animationComplete == false && this->haveCinematic() == true) {
        if (currentFrame == 1) {
            _mediator->notify("RenderingEngine", "backgroundMusicStop2");
            _mediator->notify("RenderingEngine", "game_launch_music_play");
        }
        if (cinematicsClock->getElapsedTime().asSeconds() > frameDuration) {
            if (!loadFrameTexture(texture, rectangleshape)) {
                return;
            }
            cinematicsClock->restart();
        }
    }

    window->clear();
    if (animationComplete || this->haveCinematic() == false) {
        _mediator->notify("RenderingEngine", "game_launch_music_stop");
        this->play();
        return;
    } else if (animationComplete == false && this->haveCinematic() == true) {
        RenderTexture->draw(rectangleshape);
        this->DisplaySkipIntro();
    }
    if (piou) {
        displayPiou();
        piou = false;
    }
    RenderTexture->display();
    this->handleColorblind();
    window->display();
    handleEvents();
}

void RType::Game::handleEvents() {
    sf::Event _event;
    while (window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) window->close();
        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::Space) {
                animationComplete = true;
            }
        }
    }
}

bool RType::Game::loadFrameTexture(sf::Texture& texture, sf::RectangleShape& rectangleshape) {
    frameDuration = 1.0f / 12.0f;
    std::ostringstream oss;
    oss << "assets" << PATH_SEPARATOR << "game_launch" << PATH_SEPARATOR << "Sans titre (1)_" << std::setw(3)
        << std::setfill('0') << currentFrame << ".jpg";
    std::string filename = oss.str();

    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error loading " << filename << std::endl;
        return false;
    }
    rectangleshape.setTexture(&texture);
    rectangleshape.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    currentFrame++;

    if (currentFrame > 151) {
        animationComplete = true;
    }

    return true;
}

void RType::Game::setCamera(std::shared_ptr<Camera> camera) {
    if (this->isGameOffline() == true)
        return; // Camera is loaded from client
    _camera = camera;
}

void RType::Game::setMutex(std::shared_ptr<std::mutex> mutex) {
    this->_mutex = mutex;
}

bool RType::Game::haveCinematic() {
    if (_gameSelected == "R-Type") { // For the moment, only R-Type has a cinematic
        return true;
    }
    return false;
}

bool RType::Game::isGameOffline() {
    // Need to fix this method to play offline with R-Type
    if (_gameSelected == "R-Type") {
        return false;
    }
    return true;
}


void RType::Game::displayEnemyHealth(sf::RenderWindow& win) {
    auto& healths = _registry->get_components<Health>();
    auto& positions = _registry->get_components<Position>();
    auto& controllables = _registry->get_components<Controllable>();

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    sf::Font hpFont;
    if (!hpFont.loadFromFile(fontPath)) {
        return;
    }

    for (size_t i = 0; i < healths.size(); ++i) {
        auto& health = healths[i];
        auto& position = positions[i];
        auto& controllable = controllables[i];

        if (health && position && !controllable) {
            sf::Text hpText;
            hpText.setFont(hpFont);
            hpText.setString(std::to_string(health->health) + "/" + std::to_string(health->maxHealth));
            hpText.setCharacterSize(18);
            hpText.setFillColor(sf::Color::White);

            hpText.setPosition(position->x, position->y - 20.0f);

            win.draw(hpText);
        }
    }
}

void RType::Game::displayPlayerHealth(sf::RenderWindow& win) {
    auto& healths = _registry->get_components<Health>();
    auto& positions = _registry->get_components<Position>();
    auto& controllables = _registry->get_components<Controllable>();

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    sf::Font hpFont;
    if (!hpFont.loadFromFile(fontPath)) {
        return;
    }

    for (size_t i = 0; i < healths.size(); ++i) {
        auto& health = healths[i];
        auto& position = positions[i];
        auto& controllable = controllables[i];

        if (health && position && controllable) {
            sf::Text hpText;
            hpText.setFont(hpFont);
            hpText.setString(std::to_string(health->health));
            hpText.setCharacterSize(18);
            hpText.setFillColor(sf::Color::Green);

            hpText.setPosition(position->x + 60.0f, position->y - 20.0f);

            win.draw(hpText);
        }
    }
}
