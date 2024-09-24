/*
** EPITECH PROJECT, 2024
** NetworkLib
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../../shared/network/Constants.hpp"
#include "../../shared/network/LockedQueue.hpp"
#include <boost/asio.hpp>
#include <array>
#include <thread>
#include "IClient.hpp"
#include <iostream>

namespace NetworkLib {
	class Client : public IClient {
	public:
		Client(std::string host, unsigned short server_port, unsigned short local_port = 0);
		~Client();

		void send(const std::string& message) override;
		bool hasMessage() override;;
		std::string popMessage() override;;

	private:
		// Network send/receive stuff
		boost::asio::io_service io_service;
		boost::asio::ip::udp::socket socket;
		boost::asio::ip::udp::endpoint server_endpoint;
		boost::asio::ip::udp::endpoint remote_endpoint;
		std::array<char, NetworkBufferSize> recv_buffer;
		std::thread service_thread;

		// Queues for messages
		LockedQueue<std::string> incomingMessages;

		void start_receive();
		void handle_receive(const std::error_code& error, std::size_t bytes_transferred);
		void run_service();

		Client(Client&); // block default copy constructor
	};
}


#endif /* !CLIENT_HPP_ */
