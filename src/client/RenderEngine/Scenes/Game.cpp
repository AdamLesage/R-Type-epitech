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

RType::Game::Game(std::shared_ptr<sf::RenderWindow> _window)
    : currentFrame(1), frameDuration(0.05f), animationComplete(false) {
    this->window = _window;
    std::cout << "Game created and mediator is null" << std::endl;
    this->_mediator      = nullptr;
    std::string fontPath = std::string("assets") + PATH_SEPARATOR + "r-type.ttf";
    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Error loading font");
    }

    backgroundTextures.push_back(sf::Texture());
    backgroundTextures.push_back(sf::Texture());
    backgroundTextures.push_back(sf::Texture());

    std::string backgroundPath1 =
        std::string("assets") + PATH_SEPARATOR + "background" + PATH_SEPARATOR + "back.png";
    if (!backgroundTextures[0].loadFromFile(backgroundPath1)) {
        throw std::runtime_error("Error loading backgroundTexture 1");
    }

    std::string backgroundPath2 =
        std::string("assets") + PATH_SEPARATOR + "background" + PATH_SEPARATOR + "stars.png";
    if (!backgroundTextures[1].loadFromFile(backgroundPath2)) {
        throw std::runtime_error("Error loading backgroundTexture 2");
    }

    std::string backgroundPath3 =
        std::string("assets") + PATH_SEPARATOR + "background" + PATH_SEPARATOR + "planet.png";
    if (!backgroundTextures[2].loadFromFile(backgroundPath3)) {
        throw std::runtime_error("Error loading backgroundTexture 3");
    }

    std::string soundPath =
        std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "game_launch.ogg";
    if (!game_launch_sound.loadFromFile(soundPath)) {
        throw std::runtime_error("Error loading game launch sound");
    }
    game_launch_music.setBuffer(game_launch_sound);
    isShooting = false;
    std::string shootPath =
        std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "shootsounds.wav";
    if (!shoot_sound.loadFromFile(shootPath)) {
        throw std::runtime_error("Error loading shoot sound");
    }
    shoot_music.setBuffer(shoot_sound);
    std::string shootPath2 = std::string("assets") + PATH_SEPARATOR + "Sounds" + PATH_SEPARATOR + "Piou.wav";
    if (!shoot_sound2.loadFromFile(shootPath2)) {
        throw std::runtime_error("Error loading shoot sound 2");
    }
    shoot_music2.setBuffer(shoot_sound2);
    for (int i = 0; i < 3; i++) {
        backgrounds.push_back(sf::RectangleShape(sf::Vector2f(1920, 1080)));
        backgrounds[i].setTexture(&backgroundTextures[i]);
        backgrounds[i].setPosition(sf::Vector2f(0, 0));
    }
    backgrounds.push_back(sf::RectangleShape(sf::Vector2f(1920, 1080)));
    backgrounds[3].setTexture(&backgroundTextures[1]);
    backgrounds[3].setPosition(sf::Vector2f(1920, 0));
    backgrounds[1].setFillColor(sf::Color(255, 255, 255, 128)); // Set half transparency

    for (int i = 0; i < 5; i++) {
        players.push_back(sf::RectangleShape(sf::Vector2f(131.5, 58.f)));
        playerTextures.push_back(sf::Texture());
    }
    for (int i = 0; i < 5; i++) {
        std::string playerPath = std::string("assets") + PATH_SEPARATOR + "player" + PATH_SEPARATOR
                                 + "player_" + std::to_string(i + 1) + ".png";
        if (!playerTextures[i].loadFromFile(playerPath)) {
            throw std::runtime_error("Error loading playerTexture " + std::to_string(i + 1));
        }
        players[i].setTexture(&playerTextures[i]);
        players[i].setPosition(sf::Vector2f(125.f + (125.f * i), 125.f));
        players[i].setTextureRect(sf::IntRect(0, 0, 263, 116));
    }
        if (!colorblindShader[0].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Deuteranopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading deuteranopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[1].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Protanopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading protanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[2].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Tritanopia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading tritanopia shader" << std::endl;
        return;
    }
    if (!colorblindShader[3].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Achromatopsia_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading achromatopsia shader" << std::endl;
        return;
    }
    if (!colorblindShader[4].loadFromFile(std::string("assets") + PATH_SEPARATOR + "shaders" + PATH_SEPARATOR + "Normal_shader.frag", sf::Shader::Fragment)) {
        std::cerr << "Error loading normal shader" << std::endl;
        return;
    }
    sf::RenderTexture *RenderTexture2 = new sf::RenderTexture();
    RenderTexture2->create(1920, 1080);
    RenderTexture = std::shared_ptr<sf::RenderTexture>(RenderTexture2);
    settings = std::make_shared<Settings>(window);
    _registry.register_component<Position_s>();
    _registry.register_component<Velocity_s>();
    _registry.register_component<Drawable_s>();
    _registry.register_component<Controllable_s>();
    console = std::make_shared<Console>(window,RenderTexture);
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
        shoot_music2.setVolume(200);
        shoot_music2.play();
    } else {
        shoot_music2.play();
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

    _systems.control_system(_registry, *window.get(), _mediator,
                            std::bind(&RType::Game::ShootSound, this));
    // if (keyPressed == 88)
    //     ShootSound();

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

void RType::Game::handleColorblind()
{
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