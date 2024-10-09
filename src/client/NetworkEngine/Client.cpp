/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Client
*/

#include "Client.hpp"

namespace NetworkLib {
	Client::Client(std::string host, unsigned short server_port, unsigned short local_port) :
		socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), local_port)),
		service_thread(&Client::run_service, this)
	{
		try {
			boost::asio::ip::udp::resolver resolver(io_service);
			boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, std::to_string(server_port));
			boost::asio::ip::udp::resolver::iterator it = resolver.resolve(query);

			if (it == boost::asio::ip::udp::resolver::iterator()) {
				throw std::runtime_error("Unable to resolve the server address.");
			}

			server_endpoint = *it;

			// Sending an empty message to test the connection
			Client::send("");
			std::string message = "Client connected to " + host + ":" + std::to_string(server_port);
			_logger.log(RType::Logger::LogType::INFO, message.c_str());
		}
		catch (const std::exception& e) {
			std::cerr << "Failed to connect to the server: " << e.what() << std::endl;
		}
	}

	Client::~Client()
	{
		io_service.stop();
		service_thread.join();
	}

	void Client::start_receive()
	{
		socket.async_receive_from(boost::asio::buffer(recv_buffer), remote_endpoint,
			[this](std::error_code ec, std::size_t bytes_recvd){ this->handle_receive(ec, bytes_recvd); });
	}

	void Client::handle_receive(const std::error_code& error, std::size_t bytes_transferred)
	{
		if (!error) {
			std::string message(recv_buffer.data(), recv_buffer.data() + bytes_transferred);
			incomingMessages.push(message);
		} else {
			std::cout << ("Client::handle_receive: " + error.message()) << std::endl;
		}

		start_receive();
	}

	void Client::send(const std::string& message)
	{
		socket.send_to(boost::asio::buffer(message), server_endpoint);
	}

	bool Client::hasMessage()
	{
		return !incomingMessages.empty();
	}

	std::string Client::popMessage()
	{
		if (incomingMessages.empty())
			throw std::logic_error("No messages to pop");
		return incomingMessages.pop();
	}

	void Client::run_service()
	{
		start_receive();
		while (!io_service.stopped()) {
			try {
				io_service.run();
			}
			catch (const std::exception& e) {
				std::cout << ("Client: network exception: " + std::string(e.what())) << std::endl;
			}
			catch (...) {
				std::cout << ("Unknown exception in client network thread") << std::endl;
			}
		}
	}
}