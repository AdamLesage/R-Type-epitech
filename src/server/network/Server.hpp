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

		bool hasMessages() override;
		std::pair<std::string, uint32_t> popMessage() override;

		void sendToClient(const char *message, size_t size, uint32_t clientID) override;
		void sendToAll(const char *message, size_t size);

		size_t getClientCount() override;
		uint32_t getClientIdByIndex(size_t index) override;

		std::vector<std::function<void(uint32_t)>> clientDisconnectedHandlers;
	private:
		boost::asio::io_service io_service;
		boost::asio::ip::udp::socket socket;
		boost::asio::ip::udp::endpoint server_endpoint;
		boost::asio::ip::udp::endpoint _remote_endpoint;
		std::array<char, NetworkBufferSize> recv_buffer;
		std::thread service_thread;

		void start_receive();
		void handle_remote_error(const boost::asio::ip::udp::endpoint remote_endpoint);
		void handle_receive(const std::error_code& error, std::size_t bytes_transferred);
		void handle_send(std::string /*message*/, const std::error_code& /*error*/, std::size_t /*bytes_transferred*/)	{}
		void run_service();

		// Client management
		int32_t get_or_create_client_id(boost::asio::ip::udp::endpoint endpoint);
		void on_client_disconnected(int32_t id);

		void send(const char *message, size_t size, boost::asio::ip::udp::endpoint target);

		// Incoming messages queue
		LockedQueue<std::pair<std::string, uint32_t>> incomingMessages;

		// Clients of the server
		std::map<uint32_t, boost::asio::ip::udp::endpoint> clients;
		int32_t nextClientID;
		std::shared_mutex mtx;

		Server(Server&);
	};
}

#endif