/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** client
*/

#include "../utils/Factory.hpp"
#include <iostream>

int main()
{
    NetworkLib::Factory factory;

    std::unique_ptr<NetworkLib::IClient> client = factory.CreateClient("127.0.0.0", 50000, 50010);

    while (1) {
        if (client->hasMessage()) {
            std::cout << client->popMessage() << std::endl;
        }
        client->send("test\n");
    }
}
