/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Settings
*/
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

RType::Game::Game(std::shared_ptr<sf::RenderWindow> _window) : currentFrame(1), frameDuration(0.05f), animationComplete(false)
{
    this->window = _window;
    if (!font.loadFromFile("src/client/asset/r-type.ttf")) {
        throw std::runtime_error("Error loading font");
    }

    backgroundTextures.push_back(sf::Texture());
    backgroundTextures.push_back(sf::Texture());
    backgroundTextures.push_back(sf::Texture());
    if (!backgroundTextures[0].loadFromFile("src/client/asset/background/back.png")) {
        throw std::runtime_error("Error loading backgroundTexture 1");
    }

    if (!backgroundTextures[1].loadFromFile("src/client/asset/background/planet.png")) {
        throw std::runtime_error("Error loading backgroundTexture 2");
    }

    if (!backgroundTextures[2].loadFromFile("src/client/asset/background/stars.png")) {
        throw std::runtime_error("Error loading backgroundTexture 3");
    }

    for (int i = 0; i < 3; ++i) {
        backgrounds.push_back(sf::RectangleShape(sf::Vector2f(1920, 1080)));
        backgrounds[i].setTexture(&backgroundTextures[i]);
        backgrounds[i].setPosition(sf::Vector2f(0, 0));
    }

    for (int i = 0; i < 5; ++i) {
        playerTextures.push_back(sf::Texture());
        if (!playerTextures[i].loadFromFile("src/client/asset/player/player_" + std::to_string(i + 1) + ".png")) {
            throw std::runtime_error("Error loading playerTexture " + std::to_string(i + 1));
        }
    }
    player.setSize(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(sf::Vector2f(100, 100));
    
    _registry.register_component<Position_s>();
    _registry.register_component<Velocity_s>();
    _registry.register_component<Drawable_s>();
    _registry.register_component<Controllable_s>();
}

RType::Game::~Game()
{
}

void RType::Game::play()
{
    entity_t movable = _registry.spawn_entity();
    _registry.add_component<Position_s>(movable, Position_s{100.f, 100.f});
    _registry.add_component<Velocity_s>(movable, Velocity_s{0.f, 0.f});
    _registry.add_component<Drawable_s>(movable, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    _registry.get_components<Drawable_s>()[movable]->shape.setFillColor(sf::Color::Blue);
    _registry.add_component<Controllable_s>(movable, Controllable_s{});

    entity_t static_entity = _registry.spawn_entity();
    _registry.add_component<Position_s>(static_entity, Position_s{100.f, 300.f});
    _registry.add_component<Drawable_s>(static_entity, Drawable_s{sf::RectangleShape(sf::Vector2f(50.f, 50.f))});
    _registry.get_components<Drawable_s>()[static_entity]->shape.setFillColor(sf::Color::Red);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        _systems.control_system(_registry);
        _systems.position_system(_registry);
        _systems.collision_system(_registry, *window.get());

        window->clear();
        for (int i = 0; i < 3; ++i) {
            window->draw(backgrounds[i]);
        }
        _systems.draw_system(_registry, *window.get());
        // _systems.logging_system(_registry.get_components<Position_s>(), _registry.get_components<Velocity_s>());
        window->display();
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
            if (clock.getElapsedTime().asSeconds() > frameDuration) {
                if (!loadFrameTexture(texture, sprite)) {
                    return;
                }
                clock.restart();
            }
        }

        window->clear();
        if (animationComplete) {
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
