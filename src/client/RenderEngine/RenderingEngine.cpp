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

    try {
        this->_menu = std::make_unique<Menu>(window);
        this->_settings = std::make_shared<Settings>(window);
        this->_lobby    = std::make_shared<Lobby>(window);
        this->_game = std::make_shared<Game>(window);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    logger.log(RType::Logger::LogType::RTYPEINFO, "Scenes Created");
    this->_menu->setMediator(_mediator);
    this->_lobby->setMediator(_mediator);
    this->_menu->setMediator(_mediator);
    this->_game->setMediator(_mediator);
    this->_settings->setMediator(_mediator);
    this->_lobby->setCamera(_camera);
    this->_game->setCamera(_camera);
    this->_game->setMutex(_mutex);
    this->_lobby->setMutex(_mutex);
    window->setFramerateLimit(360);
    window->clear();
    _mediator->notify("RenderingEngine", "backgroundMusicPlay");
    while (window->isOpen()) {
        switch (_stateGame)
        {
        case 1:
            this->_menu->runScene(_latency);
            break;
        case 2:
            this->_lobby->runScene(_latency);
            break;
        case 3:
            this->_game->runScene(_latency);
            break;
        case 4:
            // end of game Menu
            break;
        case -1:
            window->close();
            break;
        default:
            break;
        }
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
}

void RType::RenderingEngine::setStateGame(int newState) {
    this->_stateGame = newState;
}

extern "C" RType::RenderingEngine* entryPointRenderingEngine() {
    return (new RType::RenderingEngine());
}
