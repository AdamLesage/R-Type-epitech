/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** GameEngine
*/

#include "GameEngine.hpp"

RType::GameEngine::GameEngine()
{
    // Register all components
    _registry.register_component<Camera_s>();
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

    _protocolParsing = std::make_unique<RType::ProtocolParsing>("./src/client/GameEngine/protocol_config.cfg", _registry);
}

RType::GameEngine::~GameEngine()
{
}


void RType::GameEngine::setEngines(std::shared_ptr<NetworkEngine> networkEngine, std::shared_ptr<RenderingEngine> renderingEngine, std::shared_ptr<PhysicEngine> physicEngine, std::shared_ptr<AudioEngine> audioEngine)
{
    _networkEngine = networkEngine;
    _renderingEngine = renderingEngine;
    _physicEngine = physicEngine;
    _audioEngine = audioEngine;
}



void RType::GameEngine::run()
{
    auto& networkEngine = _networkEngine;
    auto& renderingEngine = _renderingEngine;
    auto& physicEngine = _physicEngine;
    auto& audioEngine = _audioEngine;

    std::thread networkThread([&]() {
        try {
            networkEngine->run();
        } catch (const std::exception& e) {
            std::cerr << "Error running network engine: " << e.what() << std::endl;
        }
    });

    std::thread renderingThread([&]() {
        try {
            _mutex.lock();
            renderingEngine->run();
            _mutex.unlock();
            std::cout << "Rendering engine is running" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error running render engine: " << e.what() << std::endl;
        }
    });
    
    std::thread physicThread([&]() {
        try {
            _mutex.lock();
            physicEngine->run();
            _mutex.unlock();
        } catch (const std::exception& e) {
            std::cerr << "Error running render engine: " << e.what() << std::endl;
        }
    });

    std::thread audioThread([&]() {
        try {
            _mutex.lock();
            audioEngine->run();
            _mutex.unlock();
        } catch (const std::exception& e) {
            std::cerr << "Error running audio engine: " << e.what() << std::endl;
        }
    });

    // Wait for all threads to finish
    networkThread.join();
    renderingThread.join();
    physicThread.join();
    audioThread.join();
}

void RType::GameEngine::send(const std::string &message)
{
    _mediator->notify("GameEngine", message);
}


void RType::GameEngine::handleServerData(std::string &message)
{
    // To tests this function, notify mediator from NetworkEngine with a message which is binary data
    _protocolParsing->parseData(message.c_str());
}

void RType::GameEngine::setMediator(std::shared_ptr<IMediator> mediator)
{
    _mediator = mediator;
}

extern "C" RType::GameEngine *entryPointGameEngine()
{
    return (new RType::GameEngine());
}
