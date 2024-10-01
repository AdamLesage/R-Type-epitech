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
#include "../Mediator/IMediator.hpp"

namespace NetworkLib {
	class Client : public IClient {
	public:
		Client(std::string host, unsigned short server_port, unsigned short local_port = 0, std::shared_ptr<RType::IMediator> mediator = nullptr);
		~Client();

		/**
		 * @brief Send a message to the server
		 * 
		 * @param message the message to send
		*/
		void send(const std::string& message) override;

		/**
		 * @brief Check if the client has a message
		 * 
		 * @return true if the client has a message
		*/
		bool hasMessage() override;

		/**
		 * @brief Get the message from the server and remove it from the queue
		 * 
		 * @return the message from the server
		*/
		std::string popMessage() override;

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
		std::shared_ptr<RType::IMediator> _mediator;

		/**
		 * @brief Start the receive process
		*/
		void start_receive();

		/**
		 * @brief Handle the receive process
		 * 
		 * @param error the error code
		 * @param bytes_transferred the number of bytes transferred
		*/
		void handle_receive(const std::error_code& error, std::size_t bytes_transferred);

		/**
		 * @brief Run the service thread
		*/
		void run_service();

		Client(Client&); // block default copy constructor
	};
}


#endif /* !CLIENT_HPP_ */
