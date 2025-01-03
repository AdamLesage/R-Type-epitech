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

RType::Game::Game(std::shared_ptr<sf::RenderWindow> _window, std::string scenePath)
    : currentFrame(1), frameDuration(0.05f), animationComplete(false) {
    this->window    = _window;
    this->_mediator = nullptr;

    try {
        _cfg.readFile(scenePath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        throw std::runtime_error("Error loading config file");
    }

    if (!font.loadFromFile(std::string("assets") + PATH_SEPARATOR + "r-type.ttf")) {
        throw std::runtime_error("Error loading font");
    }
    _level = 0;

    try {
        libconfig::Setting& levelSetting = _cfg.lookup("Menu.Game.level")[_level];
        this->loadBackgroundConfig(levelSetting);

    } catch (const std::exception& e) {
        throw std::runtime_error("Error loading level settings");
    }

    // Background for colorblind filters
    backgrounds.push_back(sf::RectangleShape(sf::Vector2f(1920, 1080)));
    backgrounds[backgrounds.size() - 1].setTexture(&backgroundTextures[1]);
    backgrounds[backgrounds.size() - 1].setPosition(sf::Vector2f(1920, 0));

    // Set up colorblind shaders
    std::vector<std::string> shaderNames = {"Deuteranopia_shader.frag", "Protanopia_shader.frag",
                                            "Tritanopia_shader.frag", "Achromatopsia_shader.frag",
                                            "Normal_shader.frag"};
    // Load all shaders
    try {
        for (size_t i = 0; i < shaderNames.size(); ++i) {
            if (!colorblindShader[i].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders"
                                                      + PATH_SEPARATOR + shaderNames[i],
                                                  sf::Shader::Fragment)) {
                throw std::runtime_error("Error loading " + shaderNames[i]);
            }
        }
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Error loading shaders");
    }
    settings      = std::make_shared<Settings>(window);
    RenderTexture = std::make_shared<sf::RenderTexture>();
    RenderTexture->create(1920, 1080);
    console       = std::make_shared<Console>(window, RenderTexture);
    BackgroundClock.restart();
    _camera        = std::make_shared<Camera>();
    _isGameOffline = false;
}

RType::Game::~Game() {
}

void RType::Game::loadBackgroundConfig(libconfig::Setting& levelSetting) {
    try {
        // Retrieve background paths from config file
        libconfig::Setting& backgroundSettings = levelSetting.lookup("backgrounds");
        backgrounds.clear();
        backgroundTextures.clear();
        backgroundTextures.resize(backgroundSettings.getLength());

        for (size_t i = 0; i < backgroundTextures.size(); i++) { // Load all backgrounds textures
            libconfig::Setting& backgroundSetting = backgroundSettings[i];
            // Clean path to be Linux/Windows compatible
            std::string backgroundPath = backgroundSetting["path"];
            int transparency           = backgroundSetting["transparency"];
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

void RType::Game::play(float& latency) {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            sendStateChange(-1);
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                settings->displaySettings(true);
            }
            console->toggleDeveloperConsoleFromEvent(event);
            console->checkInput();
            if (event.key.code == sf::Keyboard::F3) {
                toolbar.open();
            }
        }
        toolbar.handleEvent(event, *window);
    }

    _systems.control_system(_registry, *window.get(), _mediator, std::bind(&RType::Game::ShootSound, this));


    if (this->isGameOffline()) {
        _currentGame->setMediator(_mediator);
        _currentGame->handleOfflineGame();
    }

    RenderTexture->clear();
    try {
        libconfig::Setting& levelSetting       = _cfg.lookup("Menu.Game.level")[_level];
        libconfig::Setting& backgroundSettings = levelSetting.lookup("backgrounds");
        
        for (size_t i = 0; i < (size_t)backgroundSettings.getLength() && backgrounds.size() != i; ++i) {
            int speedX = backgroundSettings[i]["movingSpeedX"];
            int speedY = backgroundSettings[i]["movingSpeedY"];
            
            backgrounds[i].move(speedX, speedY);
            if (backgrounds[i].getPosition().x < -1920) backgrounds[i].setPosition(1920, 0);
            if (backgrounds[i].getPosition().x > 1920) backgrounds[i].setPosition(-1920, 0);
            if (backgrounds[i].getPosition().y < -1080) backgrounds[i].setPosition(0, 1080);
            if (backgrounds[i].getPosition().y > 1080) backgrounds[i].setPosition(0, -1080);
            RenderTexture->draw(backgrounds[i]);
        }
        BackgroundClock.restart();
    } catch (std::exception& e) {
        std::cerr << "fail to load Game Backgounds" << std::endl;
    }

    this->set_texture();
    for (auto& ent : entity) {
        RenderTexture->draw(ent);
    }

    if (piou) {
        displayPiou();
        piou = false;
    }

    // If game is online display different info retrieved by server
    if (_isGameOffline == false) {
        console->displayDeveloperConsole();
        toolbar.draw(RenderTexture);

        if (toolbar.showFps) {
            metrics.displayFPS(RenderTexture);
        }   
        if (toolbar.showCpu) {
            metrics.displayCPU(RenderTexture);
        }
        if (toolbar.showMemory) {
            metrics.displayMemory(RenderTexture);
        }
        if (toolbar.showGpu) {
            metrics.displayGpuUsage(RenderTexture);
        }
        if (toolbar.showNetwork) {
        metrics.displayLatency(RenderTexture, latency);
        }
        if (toolbar.showPlayerPos) {
            sf::Vector2f pos = convertToVector2fb(_camera->listEntityToDisplay[0].position);
            metrics.displayPlayerPosition(RenderTexture, pos);
        }
        displayEntitiesHealth(RenderTexture);
    }
    window->clear();
    RenderTexture->display();
    sf::Sprite sprite(RenderTexture->getTexture());
    window->draw(sprite);
    this->handleColorblind();
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
    if (_camera == nullptr) return;
    if (this->isGameOffline() == true) { // If game is offline, camera is set in the game
        this->_camera = _currentGame->getCamera();
    }
    if (_camera == nullptr) return;

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
            sf::Texture* _texture = new sf::Texture();
            if (!_texture->loadFromFile(_camera->listEntityToDisplay[i].sprite.spritePath)) {
                std::cerr << "Failed to load texture: " << _camera->listEntityToDisplay[i].sprite.spritePath << std::endl;
            } else {
                Textures.insert(std::make_pair(_camera->listEntityToDisplay[i].sprite.spritePath, _texture));
                entity[i].setTexture(_texture);
                entity[i].setTextureRect(sf::IntRect(_camera->listEntityToDisplay[i].sprite.rectPos[0],
                                                    _camera->listEntityToDisplay[i].sprite.rectPos[1],
                                                    _camera->listEntityToDisplay[i].sprite.rectSize[0],
                                                    _camera->listEntityToDisplay[i].sprite.rectSize[1]));
            }
            entity[i].setPosition(convertToVector2fb(_camera->listEntityToDisplay[i].position));
        }
    }
}

void RType::Game::runScene(float &latency) {
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
            if (!loadFrameTexture()) {
                return;
            }
            cinematicsClock->restart();
        }
    }

    if (animationComplete || this->haveCinematic() == false) {
        _mediator->notify("RenderingEngine", "game_launch_music_stop");
        play(latency);
        return;
    } else if (animationComplete == false && this->haveCinematic() == true) {
        handleEvents();
        window->clear();
        RenderTexture->clear();
        RenderTexture->draw(rectangleshape);
        this->DisplaySkipIntro();
        RenderTexture->display();
    }
    if (piou) {
        displayPiou();
        piou = false;
    }
    sf::Sprite sprite(RenderTexture->getTexture());
    window->draw(sprite);
    this->handleColorblind();
    window->display();
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

bool RType::Game::loadFrameTexture() {
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
    if (this->isGameOffline() == true) return; // Camera is loaded from client
    _camera = camera;
}

void RType::Game::setMutex(std::shared_ptr<std::mutex> mutex) {
    this->_mutex = mutex;
}

void RType::Game::setLevel(size_t level) {
    this->_level = level;
    try {
        libconfig::Setting& levelSetting = _cfg.lookup("Menu.Game.level")[_level];
        this->loadBackgroundConfig(levelSetting);
    } catch (const std::exception& e) {
        throw std::runtime_error("Error loading level settings");
    }
}

bool RType::Game::haveCinematic() {
    if (_gameSelected == "R-Type") { // For the moment, only R-Type has a cinematic
        return true;
    }
    return false;
}

bool RType::Game::isGameOffline() {
    if (_isGameOffline == true) {
        return true;
    } else if (_isGameOffline == false
               && _gameSelected == "Platformer") { // Platformer can only be played offline
        return true;
    } else {
        return false;
    }
    return false;
}

void RType::Game::displayEntitiesHealth(std::shared_ptr<sf::RenderTexture> renderTexture) {
    std::lock_guard<std::mutex> lock(*this->_mutex.get());
    if (_camera == nullptr) return;

    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    sf::Font hpFont;
    if (!hpFont.loadFromFile(fontPath)) {
        return;
    }

    for (const auto& entityInfo : _camera->listEntityToDisplay) {
        if (entityInfo.health.health > 0) {
            sf::Text hpText;
            hpText.setFont(hpFont);
            hpText.setString(std::to_string(entityInfo.health.health) + "/" + std::to_string(entityInfo.health.maxHealth));
            hpText.setCharacterSize(18);
            hpText.setFillColor(sf::Color::White);

            hpText.setPosition(entityInfo.position.x, entityInfo.position.y - 20.0f);
            renderTexture->draw(hpText);
        }
    }
}

