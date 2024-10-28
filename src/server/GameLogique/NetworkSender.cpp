/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkSender
*/

#include "NetworkSender.hpp"

NetworkSender::NetworkSender(std::shared_ptr<NetworkLib::Server> network) {
    this->_network = network;
}

NetworkSender::~NetworkSender() {
}

void NetworkSender::sendCreatePlayer(int id, float pos_x, float pos_y, int clientId) {
    std::array<char, 13> data{};
    data[0] = 0x01;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendCreateEnemy(char type, int id, float pos_x, float pos_y, int clientId) {
    int test = (int)id;
    std::array<char, 13> data{};
    data[0] = type;
    std::memcpy(&data[1], &test, sizeof(test));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendCreateWall(int id, float pos_x, float pos_y, float size_x, float size_y, int clientId) {
    std::array<char, 21> data{};

    data[0] = 0x025;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    std::memcpy(&data[13], &size_x, sizeof(float));
    std::memcpy(&data[17], &size_y, sizeof(float));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendCreateProjectil(int id, float pos_x, float pos_y, int parent_id, int clientId) {
    std::array<char, 17> data{};
    data[0] = 0x02;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(int));
    std::memcpy(&data[9], &pos_y, sizeof(int));
    std::memcpy(&data[13], &parent_id, sizeof(int));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendCreateReward(int id, float pos_x, float pos_y, int clientId) {
    std::array<char, 13> data{};
    data[0] = 0x26;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendCreateBonus(char type, int id, float pos_x, float pos_y, int clientId) {
    std::array<char, 13> data{};
    data[0] = type;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendDeleteEntity(int id, int clientId) {
    std::array<char, 5> data{};
    data[0] = 0x29;
    std::memcpy(&data[1], &id, sizeof(int));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendPositionUpdate(int id, float pos_x, float pos_y, int clientId) {
    std::array<char, 13> data{};
    data[0] = 0x30;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendHealthUpdate(int id, int hp, int clientId) {
    std::array<char, 9> data{};
    data[0] = 0x31;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &hp, sizeof(hp));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendProjectilColision(int id_projectil, int id_entity, int clientId) {
    std::array<char, 9> data{};
    data[0] = 0x35;
    std::memcpy(&data[1], &id_projectil, sizeof(id_projectil));
    std::memcpy(&data[5], &id_entity, sizeof(id_entity));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendStateChange(int id_entity, char newState, int clientId)
{
    std::array<char, 6> data{};
    data[0] = 0x37;
    std::memcpy(&data[1], &id_entity, sizeof(id_entity));
    std::memcpy(&data[5], &newState, sizeof(newState));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}

void NetworkSender::sendDirectionUpdate(int id_entity, float x, float y, int clientId = -1)
{
    std::array<char, 13> data{};
    data[0] = 0x32;
    std::memcpy(&data[1], &id_entity, sizeof(id_entity));
    std::memcpy(&data[5], &x, sizeof(x));
    std::memcpy(&data[9], &y, sizeof(y));
    if (clientId == -1) {
        this->_network->sendToAll(data.data(), data.size());
    } else {
        this->_network->sendToClient(data.data(), data.size(), clientId);
    }
}