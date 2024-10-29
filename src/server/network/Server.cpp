/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Server
*/

#include "Server.hpp"

NetworkLib::Server::Server(unsigned short local_port)
    : socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), local_port)),
      service_thread(&Server::run_service, this), nextClientID(0L) {
    std::cout << "Starting server on port: " << local_port << std::endl;
};

NetworkLib::Server::~Server() {
    io_service.stop();
    service_thread.join();
}

void NetworkLib::Server::start_receive() {
    socket.async_receive_from(
        boost::asio::buffer(recv_buffer), _remote_endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd) { this->handle_receive(ec, bytes_recvd); });
}

void NetworkLib::Server::on_client_disconnected(int32_t id) {
    for (auto& handler : clientDisconnectedHandlers)
        if (handler) handler(id);
}

void NetworkLib::Server::handle_remote_error(const boost::asio::ip::udp::endpoint remote_endpoint) {
    bool found = false;
    int32_t id;
    for (const auto& client : clients)
        if (client.second == remote_endpoint) {
            found = true;
            id    = client.first;
            break;
        }
    if (found == false) return;

    clients.erase(id);
    on_client_disconnected(id);
}

void NetworkLib::Server::handle_receive(const std::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        try {
            auto message = std::pair<std::string, uint32_t>(
                std::string(recv_buffer.data(), recv_buffer.data() + bytes_transferred),
                get_or_create_client_id(_remote_endpoint));
            if (!message.first.empty()) incomingMessages.push(message);
            ;
        } catch (...) {
            std::cout << "handle_receive: Unknown error while parsing incoming message" << std::endl;
        }
    } else {
        std::cout << "handle_receive: error: " << error.message() << " while receiving from address "
                  << _remote_endpoint;
        handle_remote_error(_remote_endpoint);
    }

    start_receive();
}

void NetworkLib::Server::send(std::vector<char> message, boost::asio::ip::udp::endpoint target_endpoint) {
    this->socket.send_to(boost::asio::buffer(message, message.size()), target_endpoint);
}

void NetworkLib::Server::send(const char* message,
                              size_t size,
                              boost::asio::ip::udp::endpoint target_endpoint) {

    this->socket.send_to(boost::asio::buffer(message, size), target_endpoint);
}

void NetworkLib::Server::sendToClient(const char* message, size_t size, uint32_t clientID) {
    try {
        send(message, size, clients.at(clientID));
    } catch (...) {
        std::cout << "sendToClient: Unknown error while sending message to client " << clientID << std::endl;
    }
};

void NetworkLib::Server::sendToAll(const char* message, size_t size) {
    packetToSend.insert(packetToSend.end(), message, message + size);

    auto now                        = std::chrono::steady_clock::now();
    std::chrono::duration<float> fs = now - lastPacketSend;
    float elapsed_seconds           = std::chrono::duration_cast<std::chrono::milliseconds>(fs).count();

    if (packetToSend.size() >= 1000 || elapsed_seconds > 100) {
        lastPacketSend = std::chrono::steady_clock::now();
        for (auto client : clients)
            send(packetToSend, client.second);
        packetToSend.clear();
    }
}

void NetworkLib::Server::run_service() {
    start_receive();
    while (!io_service.stopped()) {
        try {
            io_service.run();
        } catch (const std::exception& e) {
            std::cout << "Server: Network exception: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Server: Network exception: unknown" << std::endl;
        }
    }
    std::cout << "Server network thread stopped" << std::endl;
};

int32_t NetworkLib::Server::get_or_create_client_id(boost::asio::ip::udp::endpoint endpoint){
    {std::shared_lock<std::shared_mutex> lock(mtx);
for (const auto& client : clients) {
    if (client.second == endpoint) return client.first;
}
} // namespace NetworkLib
// Accès en écriture exclusif (pour ajout d'un nouveau client)
{
    std::unique_lock<std::shared_mutex> lock(mtx);
    auto id = nextClientID++;
    // add client
    newConnectedClient.push(id);
    std::cout << "client Connect: " << id << std::endl;
    clients.insert({id, endpoint});
    return id;
}
}
;

size_t NetworkLib::Server::getClientCount() {
    return clients.size();
}

uint32_t NetworkLib::Server::getClientIdByIndex(size_t index) {
    auto it = clients.begin();
    for (size_t i = 0; i < index; i++)
        ++it;
    return it->first;
};

std::pair<std::string, uint32_t> NetworkLib::Server::popMessage() {
    return incomingMessages.pop();
}

bool NetworkLib::Server::hasMessages() {
    return !incomingMessages.empty();
}

bool NetworkLib::Server::hasNewClientConnected() {
    return !newConnectedClient.empty();
}

size_t NetworkLib::Server::popNewConnectedClient() {
    return this->newConnectedClient.pop();
}
