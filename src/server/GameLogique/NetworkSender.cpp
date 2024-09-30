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

}

void NetworkSender::sendCreateEnemy(size_t type, size_t id, float pos_x, float pos_y)
{

}

void NetworkSender::sendCreateWall(size_t id, float pos_x, float pos_y, float size_x, float size_y)
{

}

void NetworkSender::sendCreateProjectil(size_t id, float pos_x, float pos_y, size_t parent_id)
{

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

