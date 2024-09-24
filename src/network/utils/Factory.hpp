/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Factory
*/

#include "../client/IClient.hpp"
// #include "IServer.h"
#include <memory>
#include <string>

namespace NetworkLib
{
	class Factory
	{
	public:
		static std::unique_ptr<IClient> CreateClient(std::string host, unsigned int server_port, unsigned int client_port);
		// static std::unique_ptr<IServer> CreateServer(unsigned int port);
	};
}
