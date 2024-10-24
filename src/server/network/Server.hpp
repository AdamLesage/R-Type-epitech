/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Server
*/

#ifndef Server_HPP_
#define Server_HPP_

#include "../../shared/network/Constants.hpp"
#include "../../shared/network/LockedQueue.hpp"
#include "IServer.hpp"
#include <boost/asio.hpp>
#include <array>
#include <map>
#include <thread>
#include <shared_mutex>
#include <iostream>

namespace NetworkLib {
    class Server : public IServer {
        public:
            explicit Server(unsigned short local_port);
            virtual ~Server();

            /**
             * @brief Check if there are any incoming messages from clients.
             * @return True if there are messages available, otherwise false.
             */
            bool hasMessages() override;
            /**
             * @brief Pop the next available message from the message queue.
             * @return A pair containing the client's message (string) and client ID (uint32_t).
             */
            std::pair<std::string, uint32_t> popMessage() override;

            /**
             * @brief Check if a new client has connected.
             * @return True if there is a new client, otherwise false.
             */
            bool hasNewClientConnected();
            /**
             * @brief Pop the ID of the newly connected client from the queue.
             * @return The ID (size_t) of the newly connected client.
             */
            size_t popNewConnectedClient();

            /**
             * @brief Send a message to a specific client.
             * 
             * @param message The message data to be sent.
             * @param size The size of the message.
             * @param clientID The ID of the client to whom the message is being sent.
            */
            void sendToClient(const char* message, size_t size, uint32_t clientID) override;
            /**
             * @brief Broadcast a message to all connected clients.
             * 
             * @param message The message data to be sent.
             * @param size The size of the message.
             */
            void sendToAll(const char* message, size_t size);
            /**
             * @brief Get the total number of connected clients.
             * @return The number of connected clients.
             */
            size_t getClientCount() override;
            /**
             * @brief Get the client ID at a specific index in the client list.
             * @param index The index of the client.
             * @return The client ID (uint32_t).
             */
            uint32_t getClientIdByIndex(size_t index) override;

            /**
             * @brief List of handlers to be invoked when a client disconnects.
             */
            std::vector<std::function<void(uint32_t)>> clientDisconnectedHandlers;

        private:
            boost::asio::io_service io_service;
            boost::asio::ip::udp::socket socket;
            boost::asio::ip::udp::endpoint server_endpoint;
            boost::asio::ip::udp::endpoint _remote_endpoint;
            std::array<char, NetworkBufferSize> recv_buffer;
            std::thread service_thread;

            /**
             * @brief Initiate an asynchronous receive operation to handle incoming client data.
             */
            void start_receive();
            /**
             * @brief Handle errors occurring on the remote client-side, potentially indicating disconnection.
             * 
             * @param remote_endpoint The remote client endpoint that caused the error.
             */
            void handle_remote_error(const boost::asio::ip::udp::endpoint remote_endpoint);
            /**
             * @brief Handle the completion of a receive operation, process the data, and handle any errors.
             * 
             * @param error The error code indicating the success or failure of the receive operation.
             * @param bytes_transferred The number of bytes received.
             */
            void handle_receive(const std::error_code& error, std::size_t bytes_transferred);
            /**
             * @brief Handle the completion of a send operation, log or process errors if necessary.
             * 
             * @param message The message that was sent.
             * @param error The error code indicating the success or failure of the send operation.
             * @param bytes_transferred The number of bytes sent.
             */
            void handle_send(std::string /*message*/,
                             const std::error_code& /*error*/,
                             std::size_t /*bytes_transferred*/) {
            }
            /**
             * @brief Start the service thread that runs the IO service for network operations.
             */
            void run_service();

            /**
             * @brief Get the client ID for a given endpoint or create a new one if it does not exist.
             * 
             * @param endpoint The UDP endpoint of the client.
             * @return The client ID (int32_t).
             */
            int32_t get_or_create_client_id(boost::asio::ip::udp::endpoint endpoint);
            /**
             * @brief Trigger disconnection handlers for a specific client ID.
             * 
             * @param id The ID of the disconnected client.
             */
            void on_client_disconnected(int32_t id);

            /**
             * @brief Send a message to a specific client using a vector of char.
             * 
             * @param message The message data to send.
             * @param target_endpoint The client's endpoint.
             */
            void send(std::vector<char> message, boost::asio::ip::udp::endpoint target_endpoint);
            /**
             * @brief Send a message to a specific client using a char array.
             * 
             * @param message The message data to send.
             * @param size The size of the message.
             * @param target_endpoint The client's endpoint.
             */
            void send(const char* message, size_t size, boost::asio::ip::udp::endpoint target_endpoint);

            // Incoming messages queue
            LockedQueue<std::pair<std::string, uint32_t>> incomingMessages;
            LockedQueue<size_t> newConnectedClient;

            // Clients of the server
            std::map<uint32_t, boost::asio::ip::udp::endpoint> clients;
            int32_t nextClientID;
            std::shared_mutex mtx;

            std::vector<char> packetToSend;
            std::chrono::steady_clock::time_point lastPacketSend = std::chrono::steady_clock::now();
            Server(Server&);
    };
} // namespace NetworkLib

#endif