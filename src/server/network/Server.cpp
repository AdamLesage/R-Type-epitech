/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Server
*/

#include "Server.hpp"

namespace NetworkLib {
    Server::Server(unsigned short local_port)
        : socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), local_port)),
          service_thread(&Server::run_service, this), nextClientID(0L) {
        std::cout << "Starting server on port" << local_port;
    };

    Server::~Server() {
        io_service.stop();
        service_thread.join();
    }

    void Server::start_receive() {
        socket.async_receive_from(
            boost::asio::buffer(recv_buffer), _remote_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd) { this->handle_receive(ec, bytes_recvd); });
    }

    void Server::on_client_disconnected(int32_t id) {
        for (auto& handler : clientDisconnectedHandlers)
            if (handler) handler(id);
    }

    void Server::handle_remote_error(const boost::asio::ip::udp::endpoint remote_endpoint) {
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

    void Server::handle_receive(const std::error_code& error, std::size_t bytes_transferred) {
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

    void Server::send(std::vector<char> message, boost::asio::ip::udp::endpoint target_endpoint) {
        this->socket.send_to(boost::asio::buffer(message, message.size()), target_endpoint);
    }

    void Server::send(const char* message, size_t size, boost::asio::ip::udp::endpoint target_endpoint) {

        this->socket.send_to(boost::asio::buffer(message, size), target_endpoint);
    }

    void Server::sendToClient(const char* message, size_t size, uint32_t clientID) {
        try {
            send(message, size, clients.at(clientID));
        } catch (...) {
            std::cout << "sendToClient: Unknown error while sending message to client " << clientID
                      << std::endl;
        }
    };

    void Server::sendToAll(const char* message, size_t size) {
        packetToSend.insert(packetToSend.end(), message, message + size);
        if (packetToSend.size() < 1000) {
        } else {
            for (auto client : clients)
                send(packetToSend, client.second);
            packetToSend.clear();
        }
    }

    void Server::run_service() {
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

    int32_t Server::get_or_create_client_id(boost::asio::ip::udp::endpoint endpoint){
        {std::shared_lock<std::shared_mutex> lock(mtx);
    for (const auto& client : clients) {
        if (client.second == endpoint) return client.first;
    }
} // namespace NetworkLib
// Accès en écriture exclusif (pour ajout d'un nouveau client)
{
    std::unique_lock<std::shared_mutex> lock(mtx);
    auto id = nextClientID++;
    clients.insert({id, endpoint});
    return id;
}
}
;

size_t Server::getClientCount() {
    return clients.size();
}

uint32_t Server::getClientIdByIndex(size_t index) {
    auto it = clients.begin();
    for (size_t i = 0; i < index; i++)
        ++it;
    return it->first;
};

std::pair<std::string, uint32_t> Server::popMessage() {
    return incomingMessages.pop();
}

bool Server::hasMessages() {
    return !incomingMessages.empty();
}
}
