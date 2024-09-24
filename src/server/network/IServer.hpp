/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** IServer
*/

#ifndef IServer_HPP_
#define IServer_HPP_

#include <string>
#include <utility>

namespace NetworkLib {
	class IServer {
		public:
			virtual ~IServer() {};
			virtual bool hasMessages() = 0;
			virtual void sendToClient(const std::string& message, uint32_t clientID) = 0;
			virtual std::pair<std::string, uint32_t> popMessage() = 0;
			virtual size_t getClientCount() = 0;
			virtual uint32_t getClientIdByIndex(size_t) = 0;
	};
};

#endif