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
    std::array<char, 13> data{};
    data[0] = type;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    this->_network->sendToAll(data.data(), data.size()); 
}

void NetworkSender::sendCreateWall(size_t id, float pos_x, float pos_y, float size_x, float size_y)
{
}

void NetworkSender::sendCreateProjectil(size_t id, float pos_x, float pos_y, size_t parent_id)
{
    std::array<char, 13> data{};
    data[0] = 0x02;
    std::memcpy(&data[1], &id, sizeof(id));
    std::memcpy(&data[5], &pos_x, sizeof(float));
    std::memcpy(&data[9], &pos_y, sizeof(float));
    std::memcpy(&data[13], &parent_id, sizeof(float));
    this->_network->sendToAll(data.data(), data.size());
}

void NetworkSender::sendCreateReward(size_t id, float pos_x, float pos_y)
{

}

void NetworkSender::sendCreateBonus(size_t id, float pos_x, float pos_y)
{

}

void NetworkSender::sendDeleteEntity(size_t id)
{

}

void NetworkSender::sendPositionUpdate(size_t id, float pos_x, float pos_y)
{

}

void NetworkSender::sendHealthUpdate(size_t id, size_t hp)
{

}

void NetworkSender::sendProjectilColision(size_t id_projectil, size_t id_entity)
{

}

