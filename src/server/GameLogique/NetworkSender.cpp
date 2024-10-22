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

void NetworkSender::sendCreatePlayer(int id, float pos_x, float pos_y) {
    std::array<char, 13> data{};
    data[0] = 0x01;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateEnemy(char type, int id, float pos_x, float pos_y) {
    int test = (int)id;
    std::array<char, 13> data{};
    data[0] = type;
    std::memcpy(&data[1], &test, sizeof(test));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateWall(int id, float pos_x, float pos_y, float size_x, float size_y) {
    std::array<char, 21> data{};

    data[0] = 0x025;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    std::memcpy(&data[13], &size_x, sizeof(float));
    std::memcpy(&data[17], &size_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateProjectil(int id, float pos_x, float pos_y, int parent_id) {
    std::array<char, 17> data{};
    data[0] = 0x02;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(int));
    std::memcpy(&data[9], &pos_y, sizeof(int));
    std::memcpy(&data[13], &parent_id, sizeof(int));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateReward(int id, float pos_x, float pos_y) {
    std::array<char, 13> data{};
    data[0] = 0x26;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateBonus(char type, int id, float pos_x, float pos_y) {
    std::array<char, 13> data{};
    data[0] = type;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendDeleteEntity(int id) {
    std::array<char, 5> data{};
    data[0] = 0x29;
    std::memcpy(&data[1], &id, sizeof(int));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendPositionUpdate(int id, float pos_x, float pos_y) {
    std::array<char, 13> data{};
    data[0] = 0x30;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendHealthUpdate(int id, int hp) {
    std::array<char, 9> data{};
    data[0] = 0x31;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &hp, sizeof(hp));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendProjectilColision(int id_projectil, int id_entity) {
    std::array<char, 9> data{};
    data[0] = 0x35;
    std::memcpy(&data[1], &id_projectil, sizeof(id_projectil));
    std::memcpy(&data[5], &id_entity, sizeof(id_entity));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendPing(std::string timeCode) {
    //finir et ajouter à une méthode à protocol parsing.
    //protocl parsing fichier de config dans le constructeur de game engine, bouger le fichier de config.
    std::vector<char> data(strlen(timeCode.c_str()) + 1);
    data[0] = 0x99;
    std::memcpy(&data[1], timeCode.c_str(), strlen(timeCode.c_str()));
    std::memcpy(&data[strlen(timeCode.c_str()) + 1], "\0", 1);
    this->_network->sendToAll(data.data(), data.size());
}