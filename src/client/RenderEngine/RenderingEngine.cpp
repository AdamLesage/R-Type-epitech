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
        this->_menu     = std::make_unique<Menu>(window);
        this->_settings = std::make_shared<Settings>(window);
        this->_lobby    = std::make_shared<Lobby>(window);
        this->_endMenu  = std::make_shared<EndMenu>(window);
        std::string configPath = std::string("config") + PATH_SEPARATOR + _gameSelected + PATH_SEPARATOR + "game_config.cfg";
        this->_game = std::make_shared<Game>(window, configPath);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    logger.log(RType::Logger::LogType::RTYPEINFO, "Scenes Created");
    this->_lobby->setMediator(_mediator);
    this->_menu->setMediator(_mediator);
    this->_game->setMediator(_mediator);
    this->_endMenu->setMediator(_mediator);

    this->_lobby->setGameSelected(_gameSelected);
    this->_game->setGameSelected(_gameSelected);
    this->_endMenu->setGameSelected(_gameSelected);
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
            this->_endMenu->runScene(_latency);
            break;
        case -1:
            window->close();
            break;
        default:
            break;
        }
    }
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

void RType::RenderingEngine::setLevel(size_t level) {
    if (this->_game != nullptr) {
        this->_game->setLevel(level);
    } else {
        std::cerr << "failed to set level game is null" << std::endl;
    }
}

void RType::RenderingEngine::setOfflineMode(bool isOffline)
{
    this->_game->setOfflineMode(isOffline);
}

extern "C" RType::RenderingEngine* entryPointRenderingEngine() {
    return (new RType::RenderingEngine());
}
