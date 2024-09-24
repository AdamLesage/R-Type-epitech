/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** server
*/

#include "Server.hpp"
#include "Factory.hpp"

int main(int argc, char* argv[])
{
    NetworkLib::Factory factory;

    NetworkLib::Server server(50000);

    while (1)
    {
        sleep(1);
        server.sendToAll("test\n");
    }
}
