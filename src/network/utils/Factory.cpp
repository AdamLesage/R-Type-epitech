/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Factory
*/

#include "targetver.hpp"
#include "Factory.hpp"
#include "../client/Client.hpp"
// #include "Server.h"

namespace NetworkLib {
	std::unique_ptr<IClient> Factory::CreateClient(std::string host, unsigned int server_port, unsigned int client_port)
	{
		auto client = new Client(host, server_port, client_port);
		return std::unique_ptr<IClient>(client);
	}

	// std::unique_ptr<IServer> Factory::CreateServer(unsigned int port)
	// {
	// 	auto server = new Server(port);
	// 	return std::unique_ptr<IServer>(server);
	// }
}