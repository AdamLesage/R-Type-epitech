/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** NetworkSender
*/

#include "NetworkSender.hpp"

NetworkSender::NetworkSender(std::shared_ptr<NetworkLib::Server> network)
{
    this->_network = network;
}

NetworkSender::~NetworkSender()
{
}

void NetworkSender::sendCreatePlayer(size_t id, float pos_x, float pos_y)
{
    std::array<char, 13> data{};
    data[0] = 0x01;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateEnemy(char type, size_t id, float pos_x, float pos_y)
{
    int test = (int)id;
    std::array<char, 13> data{};
    data[0] = type;
    std::memcpy(&data[1], &test, sizeof(test));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size()); 
}

void NetworkSender::sendCreateWall(size_t id, float pos_x, float pos_y, float size_x, float size_y)
{
    std::array<char, 21> data{};

    data[0] = 0x025;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    std::memcpy(&data[13], &size_x, sizeof(float));
    std::memcpy(&data[17], &size_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateProjectil(size_t id, float pos_x, float pos_y, size_t parent_id)
{
    std::array<char, 17> data{};
    data[0] = 0x02;
    std::cout << "projectil pos: " << pos_x << ":" << pos_y << std::endl;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(int));
    std::memcpy(&data[9], &pos_y, sizeof(int));
    std::memcpy(&data[13], &parent_id, sizeof(size_t));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateReward(size_t id, float pos_x, float pos_y)
{
    std::array<char, 13> data{};
    data[0] = 0x26;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateBonus(char type ,size_t id, float pos_x, float pos_y)
{
    std::array<char, 13> data{};
    data[0] = type;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendDeleteEntity(size_t id)
{
    std::array<char, 5> data{};
    data[0] = 0x29;
    std::memcpy(&data[1], &id, sizeof(int));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendPositionUpdate(size_t id, float pos_x, float pos_y)
{
    std::array<char, 13> data{};
    data[0] = 0x30;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendHealthUpdate(size_t id, size_t hp)
{
    std::array<char, 9> data{};
    data[0] = 0x30;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &hp, sizeof(hp));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendProjectilColision(size_t id_projectil, size_t id_entity)
{
    std::array<char, 9> data{};
    data[0] = 0x35;
    std::memcpy(&data[1], &id_projectil, sizeof(id_projectil));
    std::memcpy(&data[5], &id_entity, sizeof(id_entity));
    this->_network->sendToAll(data.data(), data.size());
}

