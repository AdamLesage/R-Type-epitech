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
        return;
    }
    if (event.find("create_entity ") == 0) { // Create an entity 
        std::string numbers_str = event.substr(14);
        std::istringstream iss(numbers_str);
        int entity_type, pos_x, pos_y;
        if (!(iss >> entity_type >> pos_x >> pos_y)) {
            std::cerr << "Erreur: le format du message est incorrect !" << std::endl;
            return;
        }
        char data[10];
        data[0] = 0x42;  // Create entity in protocol
        char entity_c;
        if (entity_type == 1)
            entity_c = 0x03;
        else if (entity_type == 2)
            entity_c = 0x04;
        else if (entity_type == 3)
            entity_c = 0x05;
        else if (entity_type == 4)
            entity_c = 0x06;
        else 
            entity_c = 0x03;
        data[1] = entity_c;
        std::memcpy(&data[2], &pos_x, sizeof(int));
        std::memcpy(&data[6], &pos_y, sizeof(int));
        std::string data_str(data, sizeof(data));
        this->_networkEngine->_client->send(data_str);
        return;
    }
    if (event.find("delete_entity ") == 0) { // Delete an entity 
        std::string numbers_str = event.substr(14);
        std::istringstream iss(numbers_str);
        int entity_ID;
        if (!(iss >> entity_ID)) {
            std::cerr << "Error: Bad format of message !" << std::endl;
            return;
        }
        char data[5];
        data[0] = 0x43;  // Delete entity in protocol
        std::memcpy(&data[1], &entity_ID, sizeof(int));
        std::string data_str(data, sizeof(data));
        this->_networkEngine->_client->send(data_str);
        return;
    }
    if (event.find("create_wave") == 0) { // Create a wave
        char data[1];
        data[0] = 0x44;  // Create wave in protocl
        std::string data_str(data, sizeof(data));
        this->_networkEngine->_client->send(data_str);
        return;
    }
    if (event.find("god_mode ") == 0) { // enable/disable godmode
        std::string numbers_str = event.substr(9);
        std::istringstream iss(numbers_str);
        int value;
        if (!(iss >> value)) {
            std::cerr << "Error: Bad format of message !" << std::endl;
            return;
        }
        char data[2];
        data[0] = 0x45;  // enable/disable godmode in protocol
        if (value == 1)
            data[1] = 0x01;
        if (value == 0)
            data[1] = 0x02;
        std::string data_str(data, sizeof(data));
        this->_networkEngine->_client->send(data_str);
        return;
    }
    if (event.find("shoot_speed ") == 0) { // set value of shoot speed
        std::string numbers_str = event.substr(12);
        std::istringstream iss(numbers_str);
        float value;
        if (!(iss >> value)) {
            std::cerr << "Error: Bad format of message !" << std::endl;
            return;
        }
        if (value < 0.1)
            value = 0.1;
        char data[5];
        data[0] = 0x46;  // set value of shoot speed in protocol
        std::memcpy(&data[1], &value, sizeof(float));
        std::string data_str(data, sizeof(data));
        this->_networkEngine->_client->send(data_str);
        return;
    }
    if (event.find("teleport ") == 0) { // Teleport an entity 
        std::string numbers_str = event.substr(9);
        std::istringstream iss(numbers_str);
        int pos_x, pos_y;
        if (!(iss >> pos_x >> pos_y)) {
            std::cerr << "Erreur: le format du message est incorrect !" << std::endl;
            return;
        }
        char data[10];
        data[0] = 0x47;  // Teleport entity in protocol
        std::memcpy(&data[2], &pos_x, sizeof(int));
        std::memcpy(&data[6], &pos_y, sizeof(int));
        std::string data_str(data, sizeof(data));
        this->_networkEngine->_client->send(data_str);
        return;
    }
    if (event.find("set_lives ") == 0) { // set lives of player
        std::string numbers_str = event.substr(10);
        std::istringstream iss(numbers_str);
        int value;
        if (!(iss >> value)) {
            std::cerr << "Error: Bad format of message !" << std::endl;
            return;
        }
        value *= 10;
        char data[5];
        data[0] = 0x48;  // set lives of player in protocol
        std::memcpy(&data[1], &value, sizeof(int));
        std::string data_str(data, sizeof(data));
        this->_networkEngine->_client->send(data_str);
        return;
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