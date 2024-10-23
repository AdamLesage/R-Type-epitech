/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** RenderingEngine
*/

#include "RenderingEngine.hpp"

RType::RenderingEngine::RenderingEngine() {
}

RType::RenderingEngine::~RenderingEngine() {
}

void RType::RenderingEngine::run() {
    logger.log(RType::Logger::LogType::RTYPEINFO, "RenderingEngine created");
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type");
    _menu  = std::make_unique<Menu>(window, std::shared_ptr<IMediator>(this->_mediator));
    logger.log(RType::Logger::LogType::RTYPEINFO, "Menu created");
    try {
        settings = std::make_shared<Settings>(window);
        lobby    = std::make_shared<Lobby>(window);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    this->lobby->setMediator(_mediator);
    this->_menu->setMediator(_mediator);
    if (this->_camera == nullptr) {
        std::cout << "run camera null" << std::endl;
    }
    this->lobby->setCamera(_camera);
    this->lobby->setMutex(_mutex);
    window->setFramerateLimit(360);
    window->clear();
    while (window->isOpen()) {
        int scene = _menu->displayMenu();
        if (scene == 1) {
            lobby->displayLobby(this->_latency);
        } else if (scene == 2) {
            settings->displaySettings(false);
        } else if (scene == 3) {
            window->close();
        }
        window->display();
    }
    exit(0);
}

void RType::RenderingEngine::setMediator(std::shared_ptr<IMediator> mediator) {
    _mediator = mediator;
}

void RType::RenderingEngine::setCamera(std::shared_ptr<Camera>& camera) {
    _camera = camera;
}

void RType::RenderingEngine::setMutex(std::shared_ptr<std::mutex> mutex) {
    this->_mutex = mutex;
}

void RType::RenderingEngine::setLatency(float latency) {
    _latency = latency;
    // std::cout << "Latency FROM SETTER: " << _latency << std::endl;
}

extern "C" RType::RenderingEngine* entryPointRenderingEngine() {
    return (new RType::RenderingEngine());
}
