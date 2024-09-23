/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <boost/asio.hpp>
#include <string>
#include <iostream>

class Network {
    public:
        Network(boost::asio::io_service& io_service) 
        : socket_(io_service), io_service_(io_service) {}

        // Connect to a remote endpoint
        void connect(const std::string& host, const std::string& port) {
            boost::asio::ip::tcp::resolver resolver(io_service_);
            boost::asio::ip::tcp::resolver::query query(host, port);
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
            boost::asio::connect(socket_, endpoint_iterator);
        }

        // Send data to the remote endpoint
        void send(const std::string& data) {
            boost::asio::write(socket_, boost::asio::buffer(data));
        }

        // Receive data from the remote endpoint
        std::string receive() {
            boost::asio::streambuf buffer;
            boost::system::error_code ec;
            size_t bytesRead = boost::asio::read_until(socket_, buffer, "\n", ec);
            if (ec == boost::asio::error::eof) {
                // Connection closed by the client
                throw std::runtime_error("Connection closed by the client");
            } else if (ec) {
                // Other error occurred
                throw std::runtime_error("Error reading from socket: " + ec.message());
            }
            std::string data = boost::asio::buffer_cast<const char*>(buffer.data());
            return data;
        }

        boost::asio::ip::tcp::socket socket_;
        boost::asio::io_service& io_service_;
};

#endif /* !NETWORK_HPP_ */
