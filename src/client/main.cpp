/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** client
*/

#include <iostream>
#include <memory>
#include "network/Client.hpp"

int main()
{
    std::unique_ptr<NetworkLib::IClient> client = std::make_unique<NetworkLib::Client>("127.0.0.0", 50000, 50010);

    while (1) {
        if (client->hasMessage()) {
            std::cout << client->popMessage() << std::endl;
        }
        client->send("test\n");
    }
}
