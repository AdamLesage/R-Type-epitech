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
    : currentFrame(1), frameDuration(0.05f), animationComplete(false)
{
    this->window         = _window;
    this->_mediator      = nullptr;
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

            backgrounds.push_back(sf::RectangleShape(sf::Vector2f(1920, 1080)));
            backgrounds[i].setTexture(&backgroundTextures[i]);
            backgrounds[i].setPosition(sf::Vector2f(0, 0));
            if (transparency != 0) {
                backgrounds[i].setFillColor(sf::Color(255, 255, 255, transparency)); // Set transparency
            }
        }
    } catch (const libconfig::SettingNotFoundException& e) {
        throw std::runtime_error("Error loading background settings");
    }

    try {
        // Retrieve sounds paths from config file
        libconfig::Setting& soundSettings = _cfg.lookup("Menu.Game.sounds");

        if (!game_launch_sound.loadFromFile(soundSettings["lauchSound"])) { // Load game launch sound
            throw std::runtime_error("Error loading game launch sound");
        }

        if (!shoot_sound.loadFromFile(soundSettings["shootSound"])) { // Load shoot sound
            throw std::runtime_error("Error loading shoot sound");
        }

        // Load all sounds
        game_launch_music.setBuffer(game_launch_sound);
        shoot_music.setBuffer(shoot_sound);
    } catch (const libconfig::SettingNotFoundException& e) {
        throw std::runtime_error("Error loading sound settings");
    }

    // Background for colorblind filters
    backgrounds.push_back(sf::RectangleShape(sf::Vector2f(1920, 1080)));
    backgrounds[3].setTexture(&backgroundTextures[1]);
    backgrounds[3].setPosition(sf::Vector2f(1920, 0));

    try {
        // Load all player textures
        libconfig::Setting& playerSettings = _cfg.lookup("Menu.Game.players");
        this->playerTextures.resize(playerSettings.getLength());
        this->players.resize(playerSettings.getLength());

        for (size_t i = 0; i < playerTextures.size(); i++) {
            libconfig::Setting& playerSetting = playerSettings[i];
            std::string playerPath = playerSetting["path"];
            #ifdef _WIN32
                std::replace(playerPath.begin(), playerPath.end(), '/', '\\');
            #else
                std::replace(playerPath.begin(), playerPath.end(), '\\', '/');
            #endif

            if (!playerTextures[i].loadFromFile(playerPath)) {
                throw std::runtime_error("Error loading playerTexture " + std::to_string(i + 1));
            }

            players[i].setTexture(&playerTextures[i]);
            players[i].setPosition(sf::Vector2f(125.f + (125.f * i), 125.f));
            players[i].setTextureRect(sf::IntRect(0, 0, 263, 116));
        }
    } catch (const libconfig::SettingNotFoundException& e) {
        throw std::runtime_error("Error loading player settings");
    }

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
    int random = rand() % 10;
    if (random == 9) {
        shoot_music.setVolume(200);
        shoot_music.play();
    } else {
        shoot_music.play();
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

    _systems.control_system(_registry, *window.get(), _mediator, std::bind(&RType::Game::ShootSound, this));

    window->clear();
    if (BackgroundClock.getElapsedTime().asSeconds() > 0.01f) {
        backgrounds[1].move(-2.f, 0.f);
        backgrounds[3].move(-2.f, 0.f);
        backgrounds[2].move(-1.f, 0.f);
        BackgroundClock.restart();
    }
    if (backgrounds[1].getPosition().x < -1920) backgrounds[1].setPosition(1920, 0);
    if (backgrounds[2].getPosition().x < -1920) backgrounds[2].setPosition(1920, 0);
    if (backgrounds[3].getPosition().x < -1920) backgrounds[3].setPosition(1920, 0);
    for (int i = 0; i < 4; i++) {
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

    for (int i = 0; i < (int)_camera->listEntityToDisplay.size(); i++) {
        entity.push_back(sf::RectangleShape(convertToVector2f(_camera->listEntityToDisplay[i].size)));
    }

    for (int i = 0; i < (int)_camera->listEntityToDisplay.size(); i++) {
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

    if (!animationComplete) {
        if (currentFrame == 1) {
            game_launch_music.play();
        }
        if (cinematicsClock->getElapsedTime().asSeconds() > frameDuration) {
            if (!loadFrameTexture(texture, rectangleshape)) {
                return;
            }
            cinematicsClock->restart();
        }
    }

    window->clear();
    if (animationComplete) {
        game_launch_music.stop();
        play();
        return;
    } else {
        RenderTexture->draw(rectangleshape);
        DisplaySkipIntro();
    }
    if (piou) {
        displayPiou();
        piou = false;
    }
    libconfig::Config cfg;
    std::string configPath = std::string("config") + PATH_SEPARATOR + "key.cfg";
    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    RenderTexture->display();
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
    this->_camera = camera;
}

void RType::Game::setMutex(std::shared_ptr<std::mutex> mutex) {
    this->_mutex = mutex;
}