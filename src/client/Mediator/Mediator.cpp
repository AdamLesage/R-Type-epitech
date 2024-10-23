/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Mediator
*/

#include "Mediator.hpp"

RType::Mediator::Mediator(std::shared_ptr<GameEngine> gameEngine,
                          std::shared_ptr<NetworkEngine> networkEngine,
                          std::shared_ptr<RenderingEngine> renderingEngine,
                          std::shared_ptr<PhysicEngine> physicEngine,
                          std::shared_ptr<AudioEngine> audioEngine)

{
    this->_gameEngine      = gameEngine;
    this->_networkEngine   = networkEngine;
    this->_renderingEngine = renderingEngine;
    this->_physicEngine    = physicEngine;
    this->_audioEngine     = audioEngine;

    this->_gameEngine->setMediator(std::shared_ptr<IMediator>(this));
    this->_networkEngine->setMediator(std::shared_ptr<IMediator>(this));
    this->_renderingEngine->setMediator(std::shared_ptr<IMediator>(this));
    this->_physicEngine->setMediator(std::shared_ptr<IMediator>(this));
    this->_audioEngine->setMediator(std::shared_ptr<IMediator>(this));
}

RType::Mediator::~Mediator() {
    this->_gameEngine->setMediator(nullptr);
    this->_networkEngine->setMediator(nullptr);
    this->_renderingEngine->setMediator(nullptr);

    this->_gameEngine      = nullptr;
    this->_networkEngine   = nullptr;
    this->_renderingEngine = nullptr;
}

void RType::Mediator::notifyGameEngine(std::string sender, const std::string& event) {
    if (sender != "GameEngine") return;
    if (event == "updateData") {
        this->_networkEngine->updateData();
    }
    // if event start with "LATENCY" send to render engine
    this->_networkEngine->_client->send(event);
}

void RType::Mediator::notifyNetworkEngine(std::string sender, const std::string& event) {
    (void)event;
    if (sender != "NetworkEngine") return;

    // if (event.rfind("updateData", 0) == 0) {
    //     event = event.substr(9); // Remove "updateData"
    this->_gameEngine->handleServerData(event);
    // }
}

void RType::Mediator::notifyRenderingEngine(std::string sender, const std::string& event) {
    if (sender != "RenderingEngine" && sender != "Game") return;
    if (sender == "Game") {
        char data[6];
        data[0]       = 0x40; // Player input in protocol
        int player_id = 1;
        std::memcpy(&data[1], &player_id, sizeof(int));
        char input = std::stoi(event);
        std::memcpy(&data[5], &input, sizeof(char));
        this->_networkEngine->_client->send(std::string(data, sizeof(data)));
        return;
    }
    if (event == "play") { // Start the game
        char data[5];
        data[0]       = 0x41; // Start game in protocol
        int player_id = 1;
        std::memcpy(&data[1], &player_id, sizeof(int));
        std::string data_str(data, sizeof(data));
        this->_networkEngine->_client->send(data_str);
    }
    if (event.rfind("LATENCY", 0) == 0) {
        std::string latency = event.substr(8);
        this->_renderingEngine->setLatency(std::stof(latency));
    }
}

void RType::Mediator::notifyPhysicEngine(std::string sender, const std::string& event) {
    (void)event;
    if (sender != "PhysicEngine") return;
}

void RType::Mediator::notifyAudioEngine(std::string sender, const std::string& event) {
    (void)event;
    if (sender != "AudioEngine") return;
}

void RType::Mediator::notify(std::string sender, const std::string& event) {
    this->notifyGameEngine(sender, event);
    this->notifyNetworkEngine(sender, event);
    this->notifyRenderingEngine(sender, event);
    this->notifyPhysicEngine(sender, event);
    this->notifyAudioEngine(sender, event);
}