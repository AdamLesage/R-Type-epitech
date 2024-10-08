/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderingEngine
*/

#include "RenderingEngine.hpp"

RType::RenderingEngine::RenderingEngine()
{
    std::cout << "Rendering Engine created" << std::endl;
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type");
    _menu = std::make_unique<Menu>(window, std::shared_ptr<IMediator>(this->_mediator));
    try {
        games = std::make_shared<Game>(window);
        settings = std::make_shared<Settings>(window);
        lobby = std::make_shared<Lobby>(window);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

RType::RenderingEngine::~RenderingEngine()
{
}

void RType::RenderingEngine::run()
{
    window->setFramerateLimit(360);
    window->clear();
    while (window->isOpen()) {
        int scene = _menu->displayMenu();
        if (scene == 1) {
            lobby->displayLobby();
        } else if (scene == 2) {
            settings->displaySettings();
        } else if (scene == 3) {
            window->close();
        } else if (scene == 4) {
            games->displayGame();
        }
        window->display();
    }
}

void RType::RenderingEngine::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
    this->lobby->setMediator(mediator);
    this->_menu->setMediator(mediator);
}

extern "C" RType::RenderingEngine *entryPointRenderingEngine()
{
    return (new RType::RenderingEngine());
}
