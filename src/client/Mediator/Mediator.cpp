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

    this->_gameEngine->handleServerData(event);
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
    if (event == "Game over offline") {
        this->_renderingEngine->setStateGame(4); // Game go to end menu screen
        return;
    }
    if (event == "Play again offline") {
        this->_renderingEngine->getCurrentGameDisplay()->getCurrentGame()->resetGame();
        this->_renderingEngine->setStateGame(2); // Show current game screen
        return;
    }
    if (event == "Menu offline") {
        this->_renderingEngine->setStateGame(1); // Show menu screen
        return;
    }
    if (event == "Exit") {
        this->_gameEngine->setEnd();
        this->_networkEngine->setEnd();
        this->_renderingEngine->setStateGame(-1); // Exit program
        exit(0);
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
    if (event == "Start offline game") {
        this->_renderingEngine->setStateGame(3); // Start the game
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
    if (event.find("StateChange ") == 0) {
        std::string numbers_str = event.substr(12);
        int gameState = std::stoi(numbers_str);
        switch (gameState) {
            case 1:
                this->_renderingEngine->setStateGame(1);
                break;
            case 2:
                this->_renderingEngine->setStateGame(2);
                break;
            case -1: {
                this->_gameEngine->setEnd();
                this->_networkEngine->setEnd();
                this->_renderingEngine->setStateGame(-1);
                break;
            }
            case 3: {
                if (_gameSelected == "R-Type") {
                    char data[5];
                    data[0]       = 0x41; // Start game in protocol
                    int player_id = 1;
                    std::memcpy(&data[1], &player_id, sizeof(int));
                    std::string data_str(data, sizeof(data));
                    this->_networkEngine->_client->send(data_str);
                } else { // Offline game selected do not need to send start game
                    
                }
                break;
            }
            default:
                break;
        }
    }
    if (event.rfind("LATENCY", 0) == 0) {
        std::string latency = event.substr(8);
        this->_renderingEngine->setLatency(std::stof(latency));
    }
    if (event == "ShootSound")
        this->_audioEngine->ShootSound();
    if (event == "game_launch_music_play")
        this->_audioEngine->launch_music_play();
    if (event == "game_launch_music_stop")
        this->_audioEngine->launch_music_stop();
    if (event == "backgroundMusicPlay")
        this->_audioEngine->backgroundMusicPlay();
    if (event == "selectSound")
        this->_audioEngine->selectSoundPlay();
    if (event == "getVolume") {
        this->_audioEngine->BackgroundMusicGetVolume();
    }
    if (event.find("adjustVolume") == 0) {
        if (event == "adjustVolume True")
             this->_audioEngine->adjustVolume(true);
        else if (event == "adjustVolume False")
             this->_audioEngine->adjustVolume(false);   
    }
    if (event == "backgroundMusicStop")
        this->_audioEngine->backgroundMusicStop();
    if (event == "backgroundMusicPlay2")
        this->_audioEngine->backgroundMusicPlay2();
    if (event == "getVolume2")
        this->_audioEngine->BackgroundMusicGetVolume2();
    if (event.find("adjustVolume2") == 0) {
        if (event == "adjustVolume2 True")
             this->_audioEngine->adjustVolume2(true);
        else if (event == "adjustVolume2 False")
             this->_audioEngine->adjustVolume2(false);   
    }

    if (event == "backgroundMusicStop2")
        this->_audioEngine->backgroundMusicStop2();
}

void RType::Mediator::notifyPhysicEngine(std::string sender, const std::string& event) {
    (void)event;
    if (sender != "PhysicEngine") return;
}

void RType::Mediator::notifyAudioEngine(std::string sender, const std::string& event) {
    (void)event;
    if (sender != "AudioEngine") return;
    if (event.find("volume =") == 0) {
        std::string numberString = event.substr(8);
        float number = std::stof(numberString);
        this->_renderingEngine->getMenu()->setVolume(number);
        this->_renderingEngine->getLobby()->setVolume(number);
    }
}

void RType::Mediator::notifyProtocolParsing(std::string sender, const std::string& event) {
    (void)event;
    if (sender != "ProtocolParsing") return;
    if (event.find("GameState") == 0) {
        std::string numberString = event.substr(10);
        int number = std::stoi(numberString);
        this->_renderingEngine->setStateGame(number);
    }
    if (event.find("GameLevel") == 0) {
        std::string levelString = event.substr(10);
        int level = std::stoi(levelString);
        this->_renderingEngine->setLevel(level);
    }
}

void RType::Mediator::notify(std::string sender, const std::string& event) {
    this->notifyGameEngine(sender, event);
    this->notifyNetworkEngine(sender, event);
    this->notifyRenderingEngine(sender, event);
    this->notifyPhysicEngine(sender, event);
    this->notifyAudioEngine(sender, event);
    this->notifyProtocolParsing(sender, event);
}