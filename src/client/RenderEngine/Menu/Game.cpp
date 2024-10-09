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

RType::Game::Game(std::shared_ptr<sf::RenderWindow> _window) : currentFrame(1), frameDuration(0.05f), animationComplete(false)
{
    this->window = _window;
    std::cout << "Game created and mediator is null" << std::endl;
    this->_mediator = nullptr;
    if (!font.loadFromFile("src/client/asset/r-type.ttf")) {
        throw std::runtime_error("Error loading font");
    }

    backgroundTextures.push_back(sf::Texture());
    backgroundTextures.push_back(sf::Texture());
    backgroundTextures.push_back(sf::Texture());
    if (!backgroundTextures[0].loadFromFile("src/client/asset/background/back.png")) {
        throw std::runtime_error("Error loading backgroundTexture 1");
    }

    if (!backgroundTextures[1].loadFromFile("src/client/asset/background/stars.png")) {
        throw std::runtime_error("Error loading backgroundTexture 2");
    }

    if (!backgroundTextures[2].loadFromFile("src/client/asset/background/planet.png")) {
        throw std::runtime_error("Error loading backgroundTexture 3");
    }

    if (!game_launch_sound.loadFromFile("src/client/asset/Sounds/game_launch.ogg")) {
        throw std::runtime_error("Error loading game launch sound");
    }
    game_launch_music.setBuffer(game_launch_sound);

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
        if (!playerTextures[i].loadFromFile("src/client/asset/player/player_" + std::to_string(i + 1) + ".png")) {
            throw std::runtime_error("Error loading playerTexture " + std::to_string(i + 1));
        }
        players[i].setTexture(&playerTextures[i]);
        players[i].setPosition(sf::Vector2f(125.f + (125.f * i), 125.f));
        players[i].setTextureRect(sf::IntRect(0, 0, 263, 116));
    }
    settings = std::make_shared<Settings>(window);
    _registry.register_component<Position_s>();
    _registry.register_component<Velocity_s>();
    _registry.register_component<Drawable_s>();
    _registry.register_component<Controllable_s>();
    BackgroundClock.restart();
}

RType::Game::~Game()
{
}

void RType::Game::play()
{
    entity_t movable = _registry.spawn_entity();
    _registry.add_component<Position_s>(movable, Position_s{100.f, 100.f});
    _registry.add_component<Velocity_s>(movable, Velocity_s{0.f, 0.f});
    _registry.add_component<Drawable_s>(movable, Drawable_s{players[1]});
    _registry.add_component<Controllable_s>(movable, Controllable_s{});

    entity_t static_entity = _registry.spawn_entity();
    _registry.add_component<Position_s>(static_entity, Position_s{100.f, 300.f});
    _registry.add_component<Drawable_s>(static_entity, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    _registry.get_components<Drawable_s>()[static_entity]->shape.setFillColor(sf::Color::Red);
    entity_t static_entity2 = _registry.spawn_entity();
    _registry.add_component<Position_s>(static_entity2, Position_s{300.f, 300.f});
    _registry.add_component<Drawable_s>(static_entity2, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    _registry.get_components<Drawable_s>()[static_entity2]->shape.setFillColor(sf::Color::Blue);
    entity_t static_entity3 = _registry.spawn_entity();
    _registry.add_component<Position_s>(static_entity3, Position_s{600.f, 300.f});
    _registry.add_component<Drawable_s>(static_entity3, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    _registry.get_components<Drawable_s>()[static_entity3]->shape.setFillColor(sf::Color::Green);
    entity_t static_entity4 = _registry.spawn_entity();
    _registry.add_component<Position_s>(static_entity4, Position_s{900.f, 300.f});
    _registry.add_component<Drawable_s>(static_entity4, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    _registry.get_components<Drawable_s>()[static_entity4]->shape.setFillColor(sf::Color::Yellow);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    settings->displaySettings(true);
                }
            }
        }

        int keyPressed = _systems.control_system(_registry, *window.get());
        _systems.position_system(_registry);
        _systems.collision_system(_registry, *window.get());
        // std::cout << "Key pressed: " << keyPressed << std::endl;
        if (keyPressed != -1 && _mediator != nullptr) {
            std::cout << "Key pressed: " << keyPressed << std::endl;
            this->_mediator->notify("Game", std::to_string(keyPressed));
        }

        window->clear();
        if (BackgroundClock.getElapsedTime().asSeconds() > 0.01f) {
            backgrounds[1].move(-2.f, 0.f);
            backgrounds[3].move(-2.f, 0.f);
            backgrounds[2].move(-1.f, 0.f);
            BackgroundClock.restart();
        }
        if (backgrounds[1].getPosition().x < -1920)
            backgrounds[1].setPosition(1920, 0);
        if (backgrounds[2].getPosition().x < -1920)
            backgrounds[2].setPosition(1920, 0);
        if (backgrounds[3].getPosition().x < -1920)
            backgrounds[3].setPosition(1920, 0);
        for (int i = 0; i < 4; i++) {
            window->draw(backgrounds[i]);
        }
        auto &positions = _registry.get_components<Position_s>();
        auto &drawables = _registry.get_components<Drawable_s>();

        for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
            auto &pos = positions[i];
            auto &draw = drawables[i];

            if (pos && draw) {
                draw->shape.setPosition(pos->x, pos->y);
                window->draw(draw->shape);
            }
        }
        for (int i; i < entity.size(); i++) {
            window->draw(entity[i]);
        }
        // _systems.logging_system(_registry.get_components<Position_s>(), _registry.get_components<Velocity_s>());
        window->display();
    }
}

sf::Vector2f RType::Game::convertToVector2f(const Size& size) {
    return sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

sf::Vector2f RType::Game::convertToVector2fb(const Position& pos) {
    return sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y));
}

void RType::Game::set_texture()
{
    entity.clear();
    for (int i = 0; i < camera->listEntityToDisplay.size(); i++) {
        entity.push_back(sf::RectangleShape(convertToVector2f(camera->listEntityToDisplay[i].size)));
    }
    for (int i = 0; i < camera->listEntityToDisplay.size(); i++) {
        if (Textures.find(camera->listEntityToDisplay[i].texturePath) != Textures.end()) {
            entity[i].setTexture(Textures[camera->listEntityToDisplay[i].texturePath]);
            entity[i].setPosition(convertToVector2fb(camera->listEntityToDisplay[i].position));
        } else {
            sf::Texture* texture = new sf::Texture();
            texture->loadFromFile(camera->listEntityToDisplay[i].texturePath);
            Textures.insert(std::make_pair(camera->listEntityToDisplay[i].texturePath, texture));
        }
    }
}

void RType::Game::displayGame()
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;

    if (!window) {
        std::cerr << "Error: Window not initialized!" << std::endl;
        return;
    }

    while (window->isOpen()) {
        handleEvents();

        if (!animationComplete) {
            if (currentFrame == 1) {
                game_launch_music.play();
            }
            if (clock.getElapsedTime().asSeconds() > frameDuration) {
                if (!loadFrameTexture(texture, sprite)) {
                    return;
                }
                clock.restart();
            }
        }

        window->clear();
        if (animationComplete) {
            game_launch_music.stop();
            play();
        } else {
            window->draw(sprite);
        }
        window->display();
    }
}

void RType::Game::handleEvents()
{
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

bool RType::Game::loadFrameTexture(sf::Texture& texture, sf::Sprite& sprite)
{
    frameDuration = 1.0f / 12.0f;
    std::ostringstream oss;
    oss << "src/client/asset/game_launch/Sans titre (1)_" << std::setw(3) << std::setfill('0') << currentFrame << ".jpg";
    std::string filename = oss.str();

    if (!texture.loadFromFile(filename)) {
        std::cerr << "Error loading " << filename << std::endl;
        return false;
    }

    sprite.setTexture(texture);
    currentFrame++;

    if (currentFrame > 151) {
        animationComplete = true;
    }

    return true;
}

void RType::Game::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
}
