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
		virtual bool hasMessage() = 0;
		virtual void send(const std::string& message) = 0;
		virtual std::string popMessage() = 0;
	};
}

#endif /* !ICLIENT_HPP_ */
