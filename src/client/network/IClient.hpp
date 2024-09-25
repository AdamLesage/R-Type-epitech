/*
** EPITECH PROJECT, 2024
** NetworkLib
** File description:
** IClient
*/

#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#include <string>

namespace NetworkLib
{
	class IClient
	{
	public:
		virtual ~IClient() {};

		/**
		 * @brief Check if the client has a message
		 * 
		 * @return true if the client has a message
		*/
		virtual bool hasMessage() = 0;

		/**
		 * @brief Send a message to the server
		 * 
		 * @param message the message to send
		*/
		virtual void send(const std::string& message) = 0;

		/**
		 * @brief Get the message from the server
		 * 
		 * @return the message from the server
		*/
		virtual std::string popMessage() = 0;
	};
}

#endif /* !ICLIENT_HPP_ */
