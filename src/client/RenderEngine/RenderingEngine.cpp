/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderingEngine
*/

#include "RenderingEngine.hpp"

RType::RenderingEngine::RenderingEngine()
{
}

RType::RenderingEngine::~RenderingEngine()
{
}

void RType::RenderingEngine::run()
{
    std::cout << "Rendering Engine created" << std::endl;
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type");
    _menu = std::make_unique<Menu>(window, std::shared_ptr<IMediator>(this->_mediator));
    std::cout << "Menu created" << std::endl;
    try {
        games = std::make_shared<Game>(window);
        settings = std::make_shared<Settings>(window);
        lobby = std::make_shared<Lobby>(window);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    this->lobby->setMediator(_mediator);
    this->_menu->setMediator(_mediator);
    if (this->_camera == nullptr) {
        std::cout << "run camera null" << std::endl;
    }
    this->lobby->setCamera(_camera);
    window->setFramerateLimit(360);
    window->clear();
    while (window->isOpen()) {
        int scene = _menu->displayMenu();
        if (scene == 1) {
            lobby->displayLobby();
        } else if (scene == 2) {
            settings->displaySettings(false);
        } else if (scene == 3) {
            window->close();
        } else if (scene == 4) {
            games->displayGame();
        }
        window->display();
    }
    exit(0);
}

void RType::RenderingEngine::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
}

void RType::RenderingEngine::setCamera(std::shared_ptr<Camera> &camera)
{
    _camera = camera;
    if (this->games != nullptr) {
        std::cout << "Render not null, use_count: " << _camera.use_count() << std::endl;
        this->games->setCamera(_camera);
    }
}

extern "C" RType::RenderingEngine *entryPointRenderingEngine()
{
    return (new RType::RenderingEngine());
}
