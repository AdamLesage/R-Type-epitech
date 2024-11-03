/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameEngine
*/

#include "GameEngine.hpp"

RType::GameEngine::GameEngine() {
    // Register all components
    _registry.register_component<Charging_s>();
    _registry.register_component<Color_s>();
    _registry.register_component<Controllable_s>();
    _registry.register_component<Damage_s>();
    _registry.register_component<Drawable_s>();
    _registry.register_component<Freeze_s>();
    _registry.register_component<Health_s>();
    _registry.register_component<Level_s>();
    _registry.register_component<Position_s>();
    _registry.register_component<Revivable_s>();
    _registry.register_component<Rotation_s>();
    _registry.register_component<Scale_s>();
    _registry.register_component<Shoot_s>();
    _registry.register_component<ShootingSpeed_s>();
    _registry.register_component<Sound_s>();
    _registry.register_component<Sprite_s>();
    _registry.register_component<Tag_s>();
    _registry.register_component<Type_s>();
    _registry.register_component<Velocity_s>();
    _registry.register_component<Size>();
    _registry.register_component<Direction>();
    _registry.register_component<Annimation>();

    std::string protocolPath = std::string("config") + PATH_SEPARATOR + std::string("protocol_config.cfg");

    this->_camera  = std::make_shared<Camera>();
    this->_mutex   = std::make_shared<std::mutex>();
    this->_systems = Systems();
    _protocolParsing =
        std::make_unique<RType::ProtocolParsing>(protocolPath, _registry, _mutex);
    try {
        std::string playerConfigPath = std::string("config") + PATH_SEPARATOR + std::string("player.cfg");
        _playerConfig.readFile(playerConfigPath.c_str());
    } catch (const libconfig::FileIOException& fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
    } catch (const libconfig::ParseException& pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                  << std::endl;
    }
    this->_gameSelected = "R-Type";
}

RType::GameEngine::~GameEngine() {
}

void RType::GameEngine::setEngines(std::shared_ptr<NetworkEngine> networkEngine,
                                   std::shared_ptr<RenderingEngine> renderingEngine,
                                   std::shared_ptr<PhysicEngine> physicEngine,
                                   std::shared_ptr<AudioEngine> audioEngine) {
    _networkEngine   = networkEngine;
    _renderingEngine = renderingEngine;
    _physicEngine    = physicEngine;
    _audioEngine     = audioEngine;
}

void RType::GameEngine::run() {
    auto& networkEngine   = _networkEngine;
    auto& renderingEngine = _renderingEngine;
    auto& physicEngine    = _physicEngine;
    auto& audioEngine     = _audioEngine;
    _mediator->setGameSelected(_gameSelected);
    _protocolParsing->setGameSelected(_gameSelected);

    std::thread networkThread([&]() {
        try {
            networkEngine->run();
        } catch (const std::exception& e) {
            std::cerr << "Error running network engine: " << e.what() << std::endl;
        }
    });

    std::thread renderingThread([&]() {
        try {
            renderingEngine->setGameSelected(_gameSelected);
            renderingEngine->setCamera(this->_camera);
            renderingEngine->setMutex(this->_mutex);
            renderingEngine->setOfflineMode(_isOffline);
            renderingEngine->run();
        } catch (const std::exception& e) {
            std::cerr << "Error running render engine: " << e.what() << std::endl;
        }
    });

    std::thread physicThread([&]() {
        try {
            physicEngine->run();
        } catch (const std::exception& e) {
            std::cerr << "Error running physic engine: " << e.what() << std::endl;
        }
    });

    std::thread audioThread([&]() {
        try {
            audioEngine->run();
        } catch (const std::exception& e) {
            std::cerr << "Error running audio engine: " << e.what() << std::endl;
        }
    });

    // Wait for all threads to finish
    while (_running) {
        this->_systems.annimation_system(this->_registry);
        this->_systems.direction_system(_registry, _playerConfig);
        updateCamera();
    }

    if (_gameSelected == "R-Type") networkThread.join();
    renderingThread.join();
    physicThread.join();
    audioThread.join();
}

void RType::GameEngine::send(const std::string& message) {
    _mediator->notify("GameEngine", message);
}

void RType::GameEngine::handleServerData(const std::string& message) {
    // To tests this function, notify mediator from NetworkEngine with a message which is binary data
    _protocolParsing->parseData(message);
    if (_isOffline == false) {
        float latency = _protocolParsing->getLatency();
        this->_mediator->notify("RenderingEngine", "LATENCY " + std::to_string(latency));
    }
}

void RType::GameEngine::setMediator(std::shared_ptr<IMediator> mediator) {
    _mediator = mediator;
    this->_protocolParsing->setMediator(mediator);
}

void RType::GameEngine::updateCamera() {
    auto& positions  = this->_registry.get_components<Position_s>();
    auto& sizes      = this->_registry.get_components<Size>();
    auto& rotations  = this->_registry.get_components<Rotation>();
    auto& directions = this->_registry.get_components<Direction>();
    auto& sprites    = this->_registry.get_components<Sprite>();
    auto& healths    = this->_registry.get_components<Health_s>();

    std::vector<EntityRenderInfo> entityRender;
    {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        entityRender.reserve(
        std::min({positions.size(), sizes.size(), rotations.size(), sprites.size(), healths.size()}));
        for (size_t i = 0; i < positions.size() && i < sizes.size() && i < directions.size()
                        && i < rotations.size() && i < sprites.size() && i < healths.size();
            ++i) {
            auto& position  = positions[i];
            auto& size      = sizes[i];
            auto& rotation  = rotations[i];
            auto& sprite    = sprites[i];
            auto& direction = directions[i];
            auto& health    = healths[i];

            try {
                if (position && size && rotation && sprite && direction && health) {
                    entityRender.push_back({size.value(), position.value(), rotation.value(), direction.value(),
                                            sprite.value(), health.value()});
                }
            } catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
                return;
            }
        }
    }
    {
        std::lock_guard<std::mutex> lock(*this->_mutex.get());
        this->_camera->listEntityToDisplay = std::move(entityRender);
    }
#ifdef _WIN32
    Sleep(10);
#else
    usleep(10000);
#endif
}

extern "C" RType::GameEngine* entryPointGameEngine() {
    return (new RType::GameEngine());
}
